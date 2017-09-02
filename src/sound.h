#ifndef SOUND_H
#define SOUND_H
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class sound {
    static sf::Music equip;
    static sf::Music beep;
    static sf::Music error;

    static sf::Clock c;
public:
    static void init();
    
    static void update();
};

#endif /* SOUND_H */
