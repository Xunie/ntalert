#include <vector>
#include "alert.h"
#include "blobs.h"
#include "network.h"
#include "sound.h"
using namespace std;


// static members
sf::Music sound::equip;
sf::Music sound::beep;
sf::Music sound::error;
sf::Clock sound::c;



void sound::init() {
    const vector<string> sounds = {
        "ghost_equip.wav",
        "ghost_equip2.wav",
        "ghost_equip3.wav",
        "ghost_equip4.wav",
        "ghost_equip5.wav"
    };

    // random startup sound
    auto startup = sounds[rand()%sounds.size()];
    equip.openFromMemory( blobs.at(startup).ptr, blobs.at(startup).size );
    equip.play();

    // rest of the sounds
    beep.openFromMemory( blobs.at("ghost_ping.wav").ptr, blobs.at("ghost_ping.wav").size );
    error.openFromMemory( blobs.at("ghost_idle_loop.wav").ptr, blobs.at("ghost_idle_loop.wav").size );
}

void sound::update() {
    uint32_t num_players = network::get_num_players();

    const uint32_t threshold = alert::get_threshold();
    if( network::is_valid() and num_players >= threshold ) {
        if( c.getElapsedTime().asSeconds() > max(1.0, 5.0-(num_players-threshold)) ) {
			// for some reason, in later versions of SFML we have to first stop the sound
			// I think in previous versions the rewinding was automatic?
			beep.stop();

			// play the beep
            beep.play();

			// reset timer
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
