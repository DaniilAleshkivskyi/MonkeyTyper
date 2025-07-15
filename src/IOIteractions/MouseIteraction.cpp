#include <SFML/Graphics.hpp>

using namespace sf;


namespace MouseIter{

    bool leftMousewasClicked(const RenderWindow& window, const Shape& shape) {

        Vector2i mousePixelPos = Mouse::getPosition(window);


        Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);


        if (shape.getGlobalBounds().contains(mouseWorldPos) && isButtonPressed(Mouse::Button::Left)) {
                return true;
        }

        return false;
    }


    bool rightMousewasClicked(const RenderWindow& window, const Shape& shape) {

        Vector2i mousePixelPos = Mouse::getPosition(window);


        Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);


        if (shape.getGlobalBounds().contains(mouseWorldPos) && isButtonPressed(Mouse::Button::Right)) {
            return true;
        }

        return false;
    }


    bool mouseHoover(const RenderWindow& window, const Shape& shape) {

        Vector2i mousePixelPos = Mouse::getPosition(window);


        Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);


        if (shape.getGlobalBounds().contains(mouseWorldPos)) {
            return true;
        }

        return false;
    }




}


