#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>

class hud_t : public sf::Drawable {
    sf::RectangleShape rect;

    bool state = false;

public:
    void draw( sf::RenderTarget &target, sf::RenderStates states ) const;

    void update();
};

extern hud_t hud;

#endif /* HUD_H */
