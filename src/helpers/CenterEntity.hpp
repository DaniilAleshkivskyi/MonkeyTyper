#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace CenterEnt {

    void RectSpTextCentre(sf::Text& text, const sf::RectangleShape& shape, const sf::RenderWindow& window);

    void RectSetCentre(sf::RectangleShape& shape, const sf::RenderWindow& window);

}

namespace CenterVecEnt {

    void RectSpTextCentre(std::vector<sf::Text>& texts,
                          std::vector<sf::RectangleShape>& rectVec,
                          const sf::RenderWindow& window);



    void RectSetVecCentre(std::vector<sf::RectangleShape>& shapes,
                          const sf::RenderWindow& window,
                          float spacing);

}
