#include "ThemeChooser.hpp"

ThemeChooser::ThemeChooser(Game& newGame) : game(newGame),
colorMap({
      {"PINK", Theme(sf::Color(215, 108, 130),sf::Color(176, 48, 82),sf::Color(255, 221, 178))},
      {"GREEN", Theme(sf::Color(192, 199, 140),sf::Color(185, 148, 112),sf::Color(185, 148, 112))},
      {"NAVY",Theme(sf::Color(34, 40, 49),sf::Color(148, 137, 121),sf::Color(57, 62, 70))},
      {"BROWN",Theme(sf::Color (111, 78, 55),sf::Color (254, 216, 177),sf::Color (166, 123, 91))}})
{}



