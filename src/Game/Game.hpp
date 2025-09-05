#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <random>


#include "../helpers/CenterEntity.hpp"
#include "../GameStates/GameState.hpp"
#include "../IOIteractions/MouseIteraction.hpp"
#include "../helpers/PlaceChooseMenu.hpp"
#include "ConfigMenu/ConfigOption.hpp"
#include "ConfigMenu/ConfigClick.hpp"
#include "../GameStates/IGameState.hpp"
#include "./GamePlay/GamePlay.hpp"
#include "BestScoresMenu/BestScoresMenu.hpp"
#include "ConfigMenu/ConfigMenu.hpp"
#include "MainMenu/MainMenu.hpp"
#include "GamePlay/GameOver/GameOver.hpp"


class Game{
public:
    Game();
    void run();
    static GameState getState();
    static void setState(GameState newState);
    static sf::Font& getFont();
    static void setFont(sf::Font& font);
    static sf::RenderWindow& getWindow();

    static sf::Color& getColorButt();
    static sf::Color& getHooverButt();
    static sf::Vector2f getButtSize();
    void setGameOverStats();
    static bool gameOverStatsRefresh;
    static bool scoresOpen;
    static sf::Color bgColor;
    static void setTheme(Theme newTheme);

    static bool justExitedPause;
    static bool themeChanged;
    static bool fontChanged;

    //color for our butts
    static  sf::Color colorButt;
    static sf::Color hooverButt;
    //size for buttons
    static sf::Vector2f buttSize;

    void update(float dt);
    void draw();

    static sf::Font font;
    static sf::RenderWindow window;
    static GameState state;
    static IsPaused isPaused;
    std::vector<std::string> wordList;
    std::fstream wordFile =  std::fstream("../words.txt");
    std::string word = std::string();
    MainMenu mainMenu;
    ConfigMenu configMenu;
    BestScoresMenu bestScoresMenu;
    PauseMenu pauseMenu;
    GamePlay gamePlay;
    GameOver gameOver;

};


