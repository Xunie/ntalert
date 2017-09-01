#ifndef NETWORK_H
#define NETWORK_H
#include <thread>
#include <SFML/Network.hpp>

// yay, crossplatform!
#ifdef _WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#endif /* WIN32 */

class network {
    static std::thread thrd;
    static volatile bool running;
    static volatile uint32_t num_players;
    static sf::Clock last_update;

public:
    static void init();
    static void cleanup();
    static uint32_t get_num_players();

private:
    static void grab_loop();
    static void update_num_players();
    static uint32_t request_global_players();
};

#endif /* NETWORK_H */
