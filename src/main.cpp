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
#include "alert.h"
#include "sound.h"
#include "network.h"
#include "hud.h"
using namespace std;


int main() {
    srand( time(NULL) );
    sound::init();
    network::init();

    sf::RenderWindow window( sf::VideoMode(600, 300), "NT Alert v0.1", sf::Style::Titlebar | sf::Style::Close );

    window.setVerticalSyncEnabled( true );

    while( window.isOpen() ) {
        sf::Event event;
        while( window.pollEvent(event) ) {
            if( event.type == sf::Event::Closed ) {
                window.close();
                break;
            }
            
            if( event.type == sf::Event::KeyPressed ) {
                uint32_t threshold = alert::get_threshold();
                if( event.key.code == sf::Keyboard::Up )
                    threshold = (threshold+1)%32;
                if( event.key.code == sf::Keyboard::Down )
                    threshold = (threshold-1)%32;
                alert::set_threshold( threshold );
            }
        }

        // update subsystems
        sound::update();
        hud.update();

        // rendering
        window.clear();

        window.draw( hud );

        window.display();
    }

    network::cleanup();
    return 0;
}
