#include <vector>
#include "sound.h"
using namespace std;


// static members
sf::Music sound::equip;
sf::Music sound::beep;
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
    beep.openFromMemory( sounds[5].first, sounds[5].second );
}

void sound::update() {
    if( current_players >= 1 ) {
        if( c.getElapsedTime().asSeconds() > max(1u, 9u-current_players) ) {
            beep.play();
            c.restart();
        }
    }
}
