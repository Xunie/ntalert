#include <iostream>
#include <sstream>
#include "alert.h"
#include "blobs.h"
#include "hud.h"
#include "network.h"
using namespace std;


hud_t hud;


void hud_t::init() {
    // font
    font.loadFromMemory( blobs.at("greenm03.ttf").ptr, blobs.at("greenm03.ttf").size );
    text.setFont( font );
    text.setCharacterSize( 18 );
    text.setPosition( sf::Vector2f(10, 230) );

    credits.setFont( font );
    credits.setCharacterSize( 18 );
    credits.setPosition( sf::Vector2f(435, 250) );
    credits.setString("Made by Xunie\n    art: RADI-8");
    credits.setFillColor( sf::Color( 255, 255, 255, 173 ) );

    // background
    background_texture.loadFromMemory( blobs.at("background.png").ptr, blobs.at("background.png").size );
    background_sprite.setTexture( background_texture );

    // indicator indicator
    const vector<pair<string, string>> vec = {
        {"blur", "hud_blur.png"},
        {"left", "hud_left.png"},
        {"right","hud_right.png"},
        {"text", "hud_text.png"},
        {"fill", "hud_fill.png"}
    };
    
    for( auto i : vec )
        textures[i.first].loadFromMemory( blobs.at(i.second).ptr, blobs.at(i.second).size );

    // this we CAN automate
    for( auto i : {"blur", "left", "right", "text", "fill"} )
        sprites.push_back( sf::Sprite( textures[i] ) );

    // do not remove, we MUST give this a valid value!
    current_sprite = &sprites[0];
}

void hud_t::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
    target.draw( background_sprite, states );
    target.draw( text, states  );
    target.draw( credits, states  );

    if( current_sprite )
        target.draw( *current_sprite, states );
}

void hud_t::update() {
    float t = since_last_change.getElapsedTime().asSeconds();

    ostringstream text_oss;

    if( network::is_valid() and since_start.getElapsedTime().asSeconds() > 7 ) {
        {
            // text box
            text_oss << "Players: " << network::get_num_players() << endl;
            text_oss << "Servers: " << network::get_num_servers() << endl;
            text_oss << "Threshold: " << alert::get_threshold() << endl;

            text.setFillColor( sf::Color::Green * sf::Color(255,255,255,173) );
        }

        {
            // do the loop animation
            if( current_sprite == &(sprites[3]) and t > 0.5 ) {
                current_sprite = &(sprites[4]);
                since_last_change.restart();
            } else if( current_sprite == &(sprites[4]) and t > 3 ) {
                current_sprite = &(sprites[3]);
                since_last_change.restart();
            } else {
                // ensure we're in either of two states
                if( current_sprite != &(sprites[3])
                and current_sprite != &(sprites[4]) )
                    current_sprite = &(sprites[3]);
            }

            // the ghost hud sprite:
            current_sprite->setColor( sf::Color::Green );
        }
    } else {
        {
            // text box
            text_oss << "ERROR: NO CONN" << endl;
            text.setFillColor( sf::Color::Red * sf::Color(255,255,255,173) );
        }
        
        {
            // random sprite glitching        
            if( since_last_change.getElapsedTime().asSeconds() > (1.0/4) ) {
                current_sprite = &(sprites[rand()%sprites.size()]);
                since_last_change.restart();
            }

            // ghost hud sprite:
            current_sprite->setColor( sf::Color::Red );
        }
    }

    current_sprite->setPosition( 300-64, (300-64)-10 );
    text.setString( text_oss.str() );
}
