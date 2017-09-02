#include "hud.h"
#include "network.h"

hud_t hud;


// binary blobs
extern unsigned char _binary_hud_blur_png_start;
extern unsigned char _binary_hud_blur_png_size;
extern unsigned char _binary_hud_left_png_start;
extern unsigned char _binary_hud_left_png_size;
extern unsigned char _binary_hud_right_png_start;
extern unsigned char _binary_hud_right_png_size;
extern unsigned char _binary_hud_text_png_start;
extern unsigned char _binary_hud_text_png_size;
extern unsigned char _binary_hud_fill_png_start;
extern unsigned char _binary_hud_fill_png_size;

hud_t::hud_t() : current_sprite(nullptr) {
    textures["blur"].loadFromMemory(  &_binary_hud_blur_png_start, (size_t) &_binary_hud_blur_png_size );
    textures["left"].loadFromMemory(  &_binary_hud_left_png_start, (size_t) &_binary_hud_left_png_size );
    textures["right"].loadFromMemory( &_binary_hud_right_png_start, (size_t) &_binary_hud_right_png_size );
    textures["text"].loadFromMemory(  &_binary_hud_text_png_start, (size_t) &_binary_hud_text_png_size );
    textures["fill"].loadFromMemory(  &_binary_hud_fill_png_start, (size_t) &_binary_hud_fill_png_size );

    // this we CAN automate
    for( auto i : {"blur", "left", "right", "text", "fill"} )
        sprites.push_back( sf::Sprite( textures[i] ) );

    // do not remove, we MUST give this a valid value!
    current_sprite = &sprites[0];
}

void hud_t::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
    if( current_sprite )
        target.draw( *current_sprite );
}

void hud_t::update() {
    float t = since_last_change.getElapsedTime().asSeconds();

    if( network::is_valid() ) {
        current_sprite->setColor( sf::Color::Green );

        // do the loop animation
        if( current_sprite == &(sprites[3]) and t > 0.25 ) {
            current_sprite = &(sprites[4]);
            since_last_change.restart();
        } else if( current_sprite == &(sprites[4]) and t > 2 ) {
            current_sprite = &(sprites[3]);
            since_last_change.restart();
        } else {
            // ensure we're in either of two states
            if( current_sprite != &(sprites[3])
            and current_sprite != &(sprites[4]) )
                current_sprite = &(sprites[3]);
        }
    } else {
        current_sprite->setColor( sf::Color::Red );

        // random sprite glitching        
        if( since_last_change.getElapsedTime().asSeconds() > (1.0/4) ) {
            current_sprite = &(sprites[rand()%sprites.size()]);
            since_last_change.restart();
        }
    }
}
