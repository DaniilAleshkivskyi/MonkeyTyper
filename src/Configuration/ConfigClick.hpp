#pragma once
#include "./ConfigOption.hpp"
#include <SFML/Graphics.hpp>

namespace ConfigClick {

    bool leftMouseLeftBWasClicked(const sf::RenderWindow& window, ConfigOption configOption);
    bool leftMouseRightBWasClicked(const sf::RenderWindow& window, ConfigOption configOption);


}
