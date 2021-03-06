#ifndef HUD_H
#define HUD_H
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class hud_t : public sf::Drawable {
    //sf::RectangleShape rect;

    std::map<std::string, sf::Texture> textures;
    std::vector<sf::Sprite> sprites;
    //std::string state;

    sf::Clock   since_last_change;
    sf::Clock   since_start;
    sf::Sprite *current_sprite;

    sf::Texture background_texture;
    sf::Sprite background_sprite;

    sf::Font font;
    sf::Text text;
    sf::Text credits;
public:
    void init();
    void draw( sf::RenderTarget &target, sf::RenderStates states ) const;

    void update();
};

extern hud_t hud;

#endif /* HUD_H */
