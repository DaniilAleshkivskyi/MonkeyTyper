#pragma once
#include "../../../GameStates/IGameState.hpp"

class PauseMenu : public IGameState {
    public:
    PauseMenu(sf::RenderWindow& newWindow);
    void init() override;
    void update(const sf::Event& event) override;
    void draw() override;
    void setDefColor() override;

    sf::RenderWindow& window;
    sf::Vector2f buttSize;
    sf::Font& font;
    sf::Color& hooverButt;
    sf::Color& colorButt;
    int charSizeButt;
    //Overlay for pause
    sf::RectangleShape pauseOverlay;
    //BUTT PAUSE
    std::vector<sf::RectangleShape> vecButtPause;
    //TEXT PAUSE
    std::vector<sf::Text> vecTextPause;

};

