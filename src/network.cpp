#include <iostream>
#include <sstream>
#include <thread>
#include "network.h"
using namespace std;

// std::optional:
#include <experimental/optional>
#include <utility>
using std::experimental::optional;


volatile bool network::running = true;
volatile uint32_t network::num_players = 0;
std::thread network::thrd;

optional<vector<pair<sf::IpAddress,uint16_t>>> request_servers( float timeout = 5.0f );
optional<uint16_t> serv_get_num_players( sf::IpAddress host, uint16_t port, float timeout = 5.0f );

void network::init() {
    thrd = thread( grab_loop );
}

void network::cleanup() {
    running = false;
    thrd.join();
}

uint32_t network::get_num_players() {
    return num_players;
}

void network::grab_loop() {
    std::random_device rd;
    std::mt19937 mt( rd() );

    while( running ) {
        num_players = request_global_players();
        
        uint64_t to_sleep = (45*1000) + (mt()%(30*1000));
        while( to_sleep > 0 and running ) {
            sf::sleep( sf::milliseconds( min(to_sleep, 10ull) ) );
            to_sleep -= min(to_sleep, 10ull);
        }
    }
}

uint32_t network::request_global_players() {
    uint32_t count = 0;

    auto servers = request_servers();
    
    for( auto s : *servers ) {
        optional<uint16_t> r = serv_get_num_players( s.first, s.second );
        if( r )
            count += *r;
    }

    return count;
}

// crafts a packet for the hl2 masterserver
string craft_packet( string filter, pair<sf::IpAddress,uint16_t> index = {"0.0.0.0", 0} ) {
    ostringstream oss;

    // magic
    oss.write("\x31\xFF", 2);

    // IP address and port
    oss << index.first << ":" << index.second << '\x00';

    // filter
    oss << filter << '\x00';

    // no reason to assert, we won't ever exceed this, not sanely at least
    //assert( oss.length() <= 1472 );

    return oss.str();
}

// decodes hl2 masterserver packet
optional<vector<pair<sf::IpAddress,uint16_t>>> decode( string buf, bool &last ) {
    // check for data size (XXX: relies on 1500 MTU all the way!)
    if( (buf.size() % 6) != 0
      or buf.size() == 0) {
        cout << "unexpected packet size" << endl;
        return {};
    }

    // check for magic
    const char magic[] = "\xff\xff\xff\xff\x66\x0a";
    if( buf.compare(0, 6, magic) != 0 ) {
        cout << "invalid magic numbers in received packet" << endl;
        return {};
    }

    // remove magic header
    buf.erase(0, 6);

    vector<pair<sf::IpAddress,uint16_t>> servers;

    istringstream iss(buf);
    while( true ) {
        pair<sf::IpAddress,uint16_t> server;

        // extract IP
        uint8_t ip[4];
        iss.read( (char*) ip, 4 );

        // extract port
        uint16_t port;
        iss.read( (char*) &port, sizeof(port) );

        // check for stream error
        if( !iss )
            return {};

        // cast to IpAddress only AFTER verifying iss is valid!
        server.first = sf::IpAddress( ip[0], ip[1], ip[2], ip[3] );
        server.second = ntohs(port);
        
        // check for packet end
        if( server.first == "0.0.0.0" ) {
            last = true;
            return servers;
        }

        // push back
        servers.push_back( server );
    }

    last = false;
    return servers;
}

// gets all servers from master server
optional<vector<pair<sf::IpAddress,uint16_t>>> request_servers( float timeout ) {
    vector<pair<sf::IpAddress,uint16_t>> servers;

    sf::UdpSocket socket;

    // initialize
    if( socket.bind(sf::Socket::AnyPort) != sf::Socket::Done ) {
        cout << "could not bind socket!" << endl;
        return {};
    }

    // hardcoded IPs because IDGAF
    const vector<string> hosts = {
        "208.64.200.39",
        "208.64.200.52",
        "208.64.200.65"
    };

    // send initial request to all servers
    for( auto h : hosts ) {
        string packet = craft_packet("\\appid\\244630");
        auto status = socket.send(packet.c_str(), packet.size(), h, 27011);
        if( status != sf::Socket::Done ) {
            cout << "fail on initial packet send" << endl;
            return {};
        }
    }

    // we need non-blocking operation for the next bit
    socket.setBlocking(false);

    // read until timeout!
    sf::Clock c;
    while( c.getElapsedTime().asSeconds() < timeout ) {
        // wow    very memory
        char buf[65536]; // much byte
        //    many number
        sf::IpAddress from_addr;
        unsigned short from_port;
        size_t received;

        string bufstr;
        // receive packet
        auto status = socket.receive(buf, sizeof(buf), received, from_addr, from_port);
        bufstr.append(buf, received);

        // wait until packet received
        if( status == sf::Socket::NotReady
         or status == sf::Socket::Partial ) {
            sf::sleep( sf::milliseconds(1) );
            continue;
        }

        // handle errors
        if( status == sf::Socket::Error ) {
            cout << "sf::UdpSocket error!" << endl;
            return {};
        }

        // docode and deal with packet
        if( status == sf::Socket::Done ) {
            cout << "got packet!" << endl;
            bool last = false;

            // decode and check packet
            auto opvec = decode(bufstr, last);
            if( !opvec ) {
                cout << "received invalid packet!" << endl;
                continue;
            } else
                c.restart(); // give time for next reply

            // append the received servers
            for( auto s : (*opvec) )
                servers.push_back(s);

            // doesn't matter what server we got the last packet from
            // we assume all servers share the same server list
            if( last )
                break;
        }
    }

    if( !(c.getElapsedTime().asSeconds() < timeout) )
        cout << "received timeout, returning list of servers" << endl;

    // remove duplicates and return all servers
    return servers;
}

// retrieves number of players from specific server
optional<uint16_t> serv_get_num_players( sf::IpAddress host, uint16_t port, float timeout ) {
    const char data[] = "\xFF\xFF\xFF\xFF" "T" "Source Engine Query";

    sf::UdpSocket socket;
    if( socket.bind(sf::Socket::AnyPort) != sf::Socket::Done ) {
        cout << "could not bind socket!" << endl;
        return {};
    }

    auto status = socket.send( data, sizeof(data), host, port );
    if( status != sf::Socket::Done ) {
        cout << "fail on initial packet send" << endl;
        throw;
    }

    // we need non-blocking operation for the next bit
    socket.setBlocking(false);

    // read until timeout!
    sf::Clock c;
    while( c.getElapsedTime().asSeconds() < timeout ) {
        // wow    very memory
        char buf[65536]; // much byte
        //    many number
        sf::IpAddress from_addr;
        unsigned short from_port;
        size_t received;

        string bufstr;
        // receive packet
        auto status = socket.receive(buf, sizeof(buf), received, from_addr, from_port);
        bufstr.append(buf, received);

        // wait until packet received
        if( status == sf::Socket::NotReady
         or status == sf::Socket::Partial ) {
            sf::sleep( sf::milliseconds(1) );
            continue;
        }

        // handle errors
        if( status == sf::Socket::Error ) {
            cout << "sf::UdpSocket error!" << endl;
            return {};
        }

        // docode and deal with packet
        if( status == sf::Socket::Done ) {
            char *ptr = buf;

            // check for magic
            if( ptr[0] != '\xff' or // check first header
                ptr[1] != '\xff' or
                ptr[2] != '\xff' or
                ptr[3] != '\xff' or
                ptr[4] != '\x49' ) // check second header
                continue;

            ptr += 5; // skip magic bytes
            ptr++; // skip protocol version byte

            ptr += strlen(ptr)+1; // skip name
            ptr += strlen(ptr)+1; // skip map
            ptr += strlen(ptr)+1; // skip folder
            ptr += strlen(ptr)+1; // skip game
            
            // check for wrong appid
            if( ptr[0] != '\x00'
             or ptr[1] != '\x00' )
                return {};

            ptr += 2; // skip appid
            uint8_t num = ptr[0];
            return num;
        }
    }
    
    // we got a timeout?
    return {};
}
