#pragma once
#include "../../../GameStates/IGameState.hpp"

class GameOver : IGameState {
public:
    GameOver(sf::RenderWindow& newWindow);

    void init() override;
    void update(const sf::Event &event) override;
    void draw() override;
    void setGameOverScore(std::string score);
    void setGameOverWords(std::string words);
    void setGameOverLastWord(std::string lastWord);

    sf::RenderWindow& window;
    sf::Font& font;
    sf::Color colorTxt;
    sf::Color hooverButt;
    sf::Color colorButt;
    sf::RectangleShape gameOverOverlay;
    sf::Vector2f buttSize;


    sf::Text gameOverText;

    sf::Text gameOverScore;

    int charSizeButt = 40;

    sf::Text gameOverWords;

    sf::Text gameOverLastWord;

    //BUTT GAMEOVER
    std::vector<sf::RectangleShape> vecButtGameOver;

    //TEXT GAMEOVER
     std::vector<sf::Text> vecTextGameOver;



};
