#pragma once
#include "../Configuration/ConfigOption.hpp"
#include "../WordEntity.hpp"
#include <vector>

#include "../GameState.hpp"


//ALL NECESSARY COMMS WAS WRITTEN IN CPP FILE


struct GamePlay {
    GamePlay(sf::RenderWindow& window,const std::vector<std::string>& wordList);


    sf::RenderWindow& window;

    sf::RectangleShape deadLine;


    static sf::Font fontT;
    static sf::Color wordColor;
    static float spawnRate;
    int lives = 0;
    static int cSize;
    bool highlight;
    static int wordSize;

    sf::Text livesText;

    static sf::RectangleShape interfaceBox;
    static sf::Text scoreText;
    static int score;


    int wordsTyped = 0;
    sf::Text statsText;

    sf::Text instr;



    std::string lastWord = "";



    std::vector<std::string> wordList;
    std::vector<std::string> wordsNow;
    std::vector<WordEntity> wordsOnScreen;



    sf::Clock spawnClock;
    sf::Clock deltaClock;
    sf::Text userTextInput;
    std::string userInput;
    sf::RectangleShape userTextInputBox;
    sf::Text txtInputBox;




    void updateParams(const sf::Font& fontT,sf::Color wordColor,float spawnRate,int lives,int wordSize,int charSize,const bool& highlighted);
    void handleInput(const sf::Event& event);
    GameState update(float dt);
    void draw();


    void scoreCounter(std::string word,float spRate);


    void reset();



    void getWordsFull(int value);

    bool notOutOfBorders();
    void newFontOutOfBorders();


    //UPDATING FOR EACH PARAM
    void updateFont(const sf::Font& newFont);
    void updateWordColor(const sf::Color& newColor);
    void updateSpawnRate(const float& newSpawnRate);
    void updateLives(const int& newLives);
    int livesValueChanged();
    void updateCSize(const int& newCSize);
    void updateHighlight(const bool& newHighlight);
    void updateWordSize(const int& newWordSize);


    std::string getGameOverScore();
    std::string getGameOverWords();
    std::string getGameOverLastWord();

};

