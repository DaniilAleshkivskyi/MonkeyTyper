#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../../GameStates/GameState.hpp"
#include "../../GameStates/IGameState.hpp"


class MainMenu : public IGameState{
    public:
    MainMenu(sf::RenderWindow& win);
    sf::RenderWindow& window;
    int charSizeButt = 40;
    sf::Font& font;

    sf::Texture monkeyTyperTexture = sf::Texture( "../assets/pics/MonkeyIsTyping2.png");
    sf::Sprite monkeyTyper;
    sf::Color& colorButt;
    sf::Color& hooverButt;
    //color for our text
    sf::Color& colorTxt;
    sf::Color& colorTxtHoover;
    //size for buttons
    sf::Vector2f buttSize;
    sf::Text nameText;
    //BUTTONS
    std::vector<sf::RectangleShape> menuButtons;
    //creating Text
    std::vector<sf::Text> menuTexts;
    void init() override;
    void draw() override;
    void update(const sf::Event& event) override;
    void setDefColor() override;
    void setTxtCenter() override;
private:


};
