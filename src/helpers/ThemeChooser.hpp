#pragma once

#include <SFML/Graphics.hpp>

#include "./Theme.hpp"
#include "../Game/Game.hpp"

class ThemeChooser {
    public:
    ThemeChooser(Game& game);
    Game& game;
    std::map<std::string,Theme> colorMap;
};

