#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fmt/ostream.h>//for writing results

#include "PauseMenu/PauseMenu.hpp"
#include "../../GameStates/GameState.hpp"
#include "../ConfigMenu/ConfigOption.hpp"
#include "WordEntity.hpp"


//ALL NECESSARY COMMS WAS WRITTEN IN CPP FILE
class GamePlay{
    public:
    GamePlay(sf::RenderWindow& window,std::vector<std::string>& wordList);

    void init();

    sf::RenderWindow& window;

    sf::RectangleShape deadLine;


    static sf::Font fontT;
    sf::Color& wordColor;
    static float spawnRate;
    int lives = 3;
    static int cSize;
    bool highlight;
    static int wordSize;

    sf::Text livesText;

    static sf::RectangleShape interfaceBox;
    static sf::Text scoreText;
    static int score;

    std::string fullWord;

    int wordsTyped = 0;
    sf::Text statsText;

    sf::Text instr;



    std::string lastWord;



    std::vector<std::string>& wordList;
    std::vector<std::string> wordsNow;
    std::vector<WordEntity> wordsOnScreen;



    sf::Clock spawnClock;
    sf::Clock deltaClock;
    sf::Text userTextInput;
    std::string userInput;
    sf::RectangleShape userTextInputBox;
    sf::Text txtInputBox;




    void updateParams(const sf::Font& fontT,sf::Color& wordColor,float spawnRate,int lives,int wordSize,int charSize,const bool& highlighted);
    void handleInput(const sf::Event& event);
    void update(float dt);
    void draw();


    void scoreCounter(std::string word,float spRate);


    void reset();



    void getWordsFull(int value);

    bool notOutOfBorders();
    void newFontOutOfBorders();


    //UPDATING FOR EACH PARAM
    void updateFont(const sf::Font& newFont);
    void updateWordColor(sf::Color newColor);
    void updateSpawnRate(float newSpawnRate);
    void updateLives(int newLives);
    int  livesValueChanged();
    void updateCSize(int newCSize);
    void updateHighlight(bool newHighlight);
    void updateWordSize(int newWordSize);


    std::string getGameOverScore();
    std::string getGameOverWords();
    std::string getGameOverLastWord();
};

