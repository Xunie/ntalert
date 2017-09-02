#include <vector>
#include "network.h"
#include "sound.h"
using namespace std;


// static members
sf::Music sound::equip;
sf::Music sound::beep;
sf::Music sound::error;
sf::Clock sound::c;



// binary blobs
extern unsigned char _binary_ghost_equip_wav_start;
extern unsigned char _binary_ghost_equip_wav_size;
extern unsigned char _binary_ghost_equip2_wav_start;
extern unsigned char _binary_ghost_equip2_wav_size;
extern unsigned char _binary_ghost_equip3_wav_start;
extern unsigned char _binary_ghost_equip3_wav_size;
extern unsigned char _binary_ghost_equip4_wav_start;
extern unsigned char _binary_ghost_equip4_wav_size;
extern unsigned char _binary_ghost_equip5_wav_start;
extern unsigned char _binary_ghost_equip5_wav_size;

extern unsigned char _binary_ghost_ping_wav_start;
extern unsigned char _binary_ghost_ping_wav_size;

extern unsigned char _binary_ghost_idle_loop_wav_start;
extern unsigned char _binary_ghost_idle_loop_wav_size;

void sound::init() {
    const vector<pair<void*, size_t>> sounds = {
        { &_binary_ghost_equip_wav_start,  (size_t) &_binary_ghost_equip_wav_size  },
        { &_binary_ghost_equip2_wav_start, (size_t) &_binary_ghost_equip2_wav_size },
        { &_binary_ghost_equip3_wav_start, (size_t) &_binary_ghost_equip3_wav_size },
        { &_binary_ghost_equip4_wav_start, (size_t) &_binary_ghost_equip4_wav_size },
        { &_binary_ghost_equip5_wav_start, (size_t) &_binary_ghost_equip5_wav_size },
        { &_binary_ghost_ping_wav_start,   (size_t) &_binary_ghost_ping_wav_size   }
    };

    // random startup sound
    auto startup = sounds[rand()%5];
    equip.openFromMemory( startup.first, startup.second );
    equip.play();

    // load the beep sound
    beep.openFromMemory( &_binary_ghost_ping_wav_start, (size_t) &_binary_ghost_ping_wav_size );
    
    // load the error sound
    error.openFromMemory( &_binary_ghost_idle_loop_wav_start, (size_t) &_binary_ghost_idle_loop_wav_size );
}

void sound::update() {
    uint32_t num_players = network::get_num_players();

    if( num_players >= 1 ) {
        if( c.getElapsedTime().asSeconds() > max(1u, 9u-num_players) ) {
            beep.play();
            c.restart();
        }
    }

    if( !network::is_valid() and network::since_last_update().asSeconds() > 5 ) {
        if( error.getStatus() == sf::SoundSource::Stopped )
            error.play();
    } else {
        if( error.getStatus() == sf::SoundSource::Playing )
            error.stop();
    }
}
