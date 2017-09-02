#include "hud.h"
#include "network.h"

hud_t hud;

void hud_t::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
    target.draw( rect );
}

void hud_t::update() {
    // set appropriate colors on rectangle
    if( !network::is_valid() )
        rect.setFillColor( sf::Color::Red );
    else
        rect.setFillColor( sf::Color::Green );

    rect.setSize( sf::Vector2f( 100, 100 ) );
}
