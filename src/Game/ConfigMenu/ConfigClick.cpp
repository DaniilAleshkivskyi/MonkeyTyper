#include "ConfigClick.hpp"

namespace ConfigClick {
    using namespace sf;

    bool leftMouseLeftBWasClicked(const RenderWindow& window, ConfigOption configOption) {

        Vector2i mousePixelPos = Mouse::getPosition(window);


        Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);


        if (configOption.leftButton.first.getGlobalBounds().contains(mouseWorldPos) && isButtonPressed(Mouse::Button::Left)) {

            return true;

        }

        return false;



    }
    bool leftMouseRightBWasClicked(const RenderWindow& window, ConfigOption configOption) {

        Vector2i mousePixelPos = Mouse::getPosition(window);

        Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

        if (configOption.rightButton.first.getGlobalBounds().contains(mouseWorldPos) && isButtonPressed(Mouse::Button::Left)) {

            return true;

        }

        return false;
    }

}
