#pragma once
#include <SFML/Graphics.hpp>

namespace MouseIter {

    bool leftMousewasClicked(const sf::RenderWindow& window, const sf::Shape& shape);

    bool rightMousewasClicked(const sf::RenderWindow& window, const sf::Shape& shape);

    bool mouseHoover(const sf::RenderWindow& window, const sf::Shape& shape);

}
