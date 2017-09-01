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
#include "sound.h"
#include "network.h"
using namespace std;







/*struct resource {
    void *ptr;
    size_t len;
}

class satconhud : public sf::Drawable {
    string state;
    
    sf::Clock c;
    float next_anim;

    void update() {
        if( next_anim < c.getElapsedTime().asSeconds() ) {
        }
    }
    
    void draw( sf::RenderTarget &target, sf::RenderStates states ) const {
    }
};*/




int main() {
    srand( time(NULL) );
    sound::init();
    network::init();

    sf::RenderWindow window( sf::VideoMode(600, 300), "NT Alert" );

    while( window.isOpen() ) {
        sf::Event event;
        while( window.pollEvent(event) ) {
            if( event.type == sf::Event::Closed ) {
                window.close();
                break;
            }
        }

        // alerter update
        sound::update();

        // rendering
        window.clear();

        window.display();
    }

    network::cleanup();
    return 0;
}
