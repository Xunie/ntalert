// generic stuff:
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// project stuff:
#include "blobs.h"
#include "config.h"
#include "alert.h"
#include "sound.h"
#include "network.h"
#include "hud.h"
using namespace std;




int main() {
    srand( time(NULL) );
    hud.init();
    sound::init();
    network::init();

    sf::RenderWindow window( sf::VideoMode(600, 300), NTALERT_TITLE, sf::Style::Titlebar | sf::Style::Close );

    window.setVerticalSyncEnabled( true );
    window.setFramerateLimit(60);

    while( window.isOpen() ) {
        // update subsystems
        sound::update();
        hud.update();

        // rendering
        window.clear();
        window.draw( hud );
        window.display();

        // handle events
        sf::Event e;
        while( window.pollEvent(e) ) {
            if( e.type == sf::Event::Closed ) {
                window.close();
                break;
            }

            if( e.type == sf::Event::KeyPressed ) {
                uint32_t &ref = alert::get_threshold();
                if( e.key.code == sf::Keyboard::Up )
                    ref = (ref + 1) % 32;
                if( e.key.code == sf::Keyboard::Down )
                    ref = (ref - 1) % 32;
            }
        }
    }

    network::cleanup();
    return 0;
}
