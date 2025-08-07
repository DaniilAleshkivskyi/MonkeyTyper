#pragma once
#include "../Game/ConfigMenu/ConfigOption.hpp"

namespace ChooseMenu {
    void RectSetVecLeft(std::vector<sf::RectangleShape>& shapes,
                          const sf::RenderWindow& window,
                          float spacing);
    void updateVecs(std::vector<ConfigOption>& configOptions);


    void ConfOptionVecLeft(std::vector<ConfigOption>& configOptions,const sf::RenderWindow& window,float spacing);
}