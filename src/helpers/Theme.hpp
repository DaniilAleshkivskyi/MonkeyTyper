#pragma once
#include <SFML/Graphics.hpp>

class Theme {
    public:
    Theme(sf::Color newBg,sf::Color newColorButt, sf::Color newHooverButt);
    sf::Color background;
    sf::Color colorButt;
    sf::Color hooverButt;
};
