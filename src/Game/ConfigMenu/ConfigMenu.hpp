#pragma once
#include "../../GameStates/IGameState.hpp"


#include <SFML/Graphics.hpp>

#include "ConfigOption.hpp"
#include "../GamePlay/GamePlay.hpp"

class ConfigMenu : public IGameState {
    public:
    ConfigMenu(sf::RenderWindow& win,GamePlay& gamePlay);

    GamePlay& gamePlay;
    sf::Font& font;
    sf::Color wordsColor;
    sf::Color defaultBackgroundColor;
    bool isWordsColorChanged;

    void init() override;
    void update(const sf::Event& event) override;
    void draw() override;

    sf::RenderWindow& window;

    int wordSizeMin;
    int wordSizeNow;
    int wordSizeMax;

    int charSizeMin;
    int charSizeNow;
    int charSizeMax;


    int livesMin;
    int livesNow;
    int livesMax;

    float wordSpawnMin;
    float wordSpawnNow;
    float wordSpawnMax;

    bool isHighlighted;


    sf::Font font2;
    sf::Font font3;
    sf::Font font4;
    sf::Font font5;
    sf::Font font6;



    std::vector<ConfigOption> configOptions;
    std::map<std::string, sf::Color> colorMap;
    std::map<std::string, sf::Font> fontMap;
    sf::RectangleShape buttonTemplate;
    sf::Text labelTemplate;
    sf::Color colorNow;
    bool isClicked;
    sf::RectangleShape startButt;
    sf::Text startText;



};
