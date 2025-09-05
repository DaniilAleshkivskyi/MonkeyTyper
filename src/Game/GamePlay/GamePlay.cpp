#include "GamePlay.hpp"
#include "../Game.hpp"


sf::RectangleShape GamePlay::interfaceBox;
sf::Font GamePlay::fontT;
float GamePlay::spawnRate;
int GamePlay::cSize;
sf::Text GamePlay::scoreText(fontT,"",cSize);
int GamePlay::score = 0;
int GamePlay::wordSize = 0;


GamePlay::GamePlay(sf::RenderWindow& window,std::vector<std::string>& wordList)
    :window(window),
    colorTxt(Game::getHooverButt()),
    colorTxtHoover(Game::getColorButt()),
    wordList(wordList),
    userTextInput(fontT,"Lives 10",40),
    livesText(fontT,"",40),
    statsText(fontT,"Correctly typed words: " + std::to_string(wordsTyped),cSize),
    instr(fontT,"For cleaning input: \"Enter\"\nTo clean previous char: \"Backspace\"",cSize),
    txtInputBox(fontT,"INPUT",cSize){}

void GamePlay::init() {

    //DEADLINE FOR WORDS
    deadLine.setSize({30,window.getSize().y - 300.f});
    deadLine.setPosition(sf::Vector2f{window.getSize().x - 100.f,0});
    deadLine.setFillColor(sf::Color::White);


    //INTERFACE BAR
    interfaceBox.setSize({(float)window.getSize().x,  300.f});
    interfaceBox.setPosition({0, window.getSize().y - interfaceBox.getSize().y});
    interfaceBox.setOutlineThickness(2.f);

    userTextInputBox.setOutlineThickness(2);
    userTextInputBox.setSize({600,100});
    userTextInputBox.setPosition({interfaceBox.getPosition().x + interfaceBox.getSize().x/2.f, interfaceBox.getPosition().y + interfaceBox.getSize().y/2.f});

    //USER INPUT
    userTextInput.setOrigin({userTextInput.getLocalBounds().size.x/2.f , userTextInput.getLocalBounds().size.y/2.f});
    userTextInput.setPosition({userTextInputBox.getPosition().x + 20, userTextInputBox.getPosition().y + userTextInputBox.getSize().y/4.f});

    livesText.setPosition({interfaceBox.getGlobalBounds().position.x + 10, interfaceBox.getGlobalBounds().position.y + 30});

    statsText.setPosition({livesText.getPosition().x,livesText.getPosition().y + 70});

    instr.setPosition({livesText.getPosition().x,statsText.getPosition().y + 70});
}



void GamePlay::updateParams(const sf::Font &newFont, sf::Color& newWordColor, float newSpawnRate, int newLives, int newWordSize, int newCharSize, const bool& newHighlighted) {
    fontT = newFont;
    spawnRate = newSpawnRate;
    lives = newLives;
    wordSize = newWordSize;
    getWordsFull(wordSize);
    cSize = newCharSize;
    highlight = newHighlighted;
    livesText.setCharacterSize(cSize);
    livesText.setFont(fontT);
    livesText.setString("Lives: " + std::to_string(lives));


    statsText.setFont(fontT);
    statsText.setCharacterSize(cSize);

    instr.setFont(fontT);
    instr.setCharacterSize(cSize);


    txtInputBox.setFont(fontT);
    txtInputBox.setCharacterSize(cSize);
    txtInputBox.setOrigin(txtInputBox.getLocalBounds().position + txtInputBox.getLocalBounds().size / 2.f);
    txtInputBox.setPosition({userTextInputBox.getPosition().x + userTextInputBox.getSize().x/2.f,userTextInputBox.getPosition().y - 30});



    scoreText.setFont(fontT);
    scoreText.setCharacterSize(40);
    scoreText.setString("Score: 0");
    scoreText.setOrigin( scoreText.getLocalBounds().position +  scoreText.getLocalBounds().size / 2.f);
    scoreText.setPosition({window.getPosition().x + window.getSize().x/2.f,30});
    macCheck();
    themeChanged();
}


//THIS METHOD HELPS US TO NOT ALLOW USER TO TYPE MORE THAN BORDERS
bool GamePlay::notOutOfBorders(){
    auto boxBounds = userTextInputBox.getGlobalBounds().position.x + userTextInputBox.getSize().x;//here we are calculating box size for having bounds with our txt
    auto txtBounds = userTextInput.getGlobalBounds().position.x + userTextInput.getLocalBounds().size.x + 40;//here we are calculating text size and adding +40 for making "bounds"

    if (boxBounds <= txtBounds) {
        return false;
    }else{
        return true;
    }
}



//THIS METHOD HELPS US TO DELETE TXT THAT GETS OUT OF userTextInputBox AFTER CHANGING FONT(IT USUALLY HAPPENS)
void GamePlay::newFontOutOfBorders(){
    auto boxBounds = userTextInputBox.getGlobalBounds().position.x + userTextInputBox.getSize().x;//here we are calculating box size for having bounds with our txt
    auto txtBounds = userTextInput.getGlobalBounds().position.x + userTextInput.getLocalBounds().size.x + 40;//here we are calculating text size and adding +40 for making "bounds"

    while (boxBounds <= txtBounds) {

        if (txtBounds <= boxBounds) break;
        if (userInput.empty()) break;



        userInput.pop_back();
        userTextInput.setString(userInput);
        txtBounds = userTextInput.getGlobalBounds().position.x + userTextInput.getLocalBounds().size.x + 40;
    }
}

//HANDLING TYPED CHARS
void GamePlay::handleInput(const sf::Event& event){
    if (const auto e = event.getIf<sf::Event::TextEntered>()){
        //CONVERTING TO UNICODE TO READ WHICH KEY WAS ENTERED
        const char charInt =  e->unicode;

        if (charInt == 8 && !userInput.empty()) {
            userInput.pop_back();// Backspace
        }else if (charInt == 13|| charInt == 10) {
            userInput.clear();//if enter -> clear word
        }


        if (notOutOfBorders()) {
            if (charInt > 64){
                userInput+=charInt;
            }
        } else {
        //if out of borders just ignoring input
        }
    }
};


//  IF -> QUIT RESETTING ALL STATS
void GamePlay::reset() {
    wordsOnScreen.clear();
    userInput.clear();
    score = 0;
    WordEntity::clearTypedPart();
    spawnClock.restart();
    scoreText.setString("Score: 0");
    statsText.setString("Correctly typed words: 0");
    wordsTyped = 0;
    lastWord = "";
}




//CLASS FOR UPDATING GAMEPLAY,DETAILS DOWNSIDE
void GamePlay::update(const float dt) {
    //SETTING INPUT STR
    userTextInput.setString(userInput);
    WordEntity::setTypedPart(userInput);

   //SPAWNING
    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate && !wordList.empty()) {
        std::string chosenWord = wordsNow[rand() % wordsNow.size()];

        float y = rand() % (int)(window.getSize().y - interfaceBox.getSize().y - 110) + 60 ;//60 - for upper bound, in rand -50 for interface bound
        float speed = rand() % 150 + 100;

        WordEntity word(chosenWord, fontT, cSize, colorTxt, {0.f, y}, speed,highlight);
        wordsOnScreen.push_back(word);

        spawnClock.restart();
    }
    //coloring everything if theme changed
    if (Game::themeChanged) {
      themeChanged();
    }




    //ERASING WORDS
    for (auto it = wordsOnScreen.begin(); it != wordsOnScreen.end(); ++it) {
        fullWord = (*it).getFullWord();
        if (fullWord == userInput) {
            scoreCounter(fullWord,spawnRate);
            wordsOnScreen.erase(it);
            lastWord = fullWord;
            wordsTyped++;
            statsText.setString("Correctly typed words: " + std::to_string(wordsTyped));

            userInput.clear();
            break;
        }
    }


    //MOVEMENT
    for (auto& word : wordsOnScreen) {
        word.getText().move({word.getSpeed() * dt, 0.f});
        if (highlight) {
            word.updateHighlight();
        }
    }


        //LIVES AND BEST SCORES WRITING
        for (auto it = wordsOnScreen.begin(); it != wordsOnScreen.end();) {
            if ((*it).getText().getPosition().x > deadLine.getPosition().x) {
                if (lives > 0) {
                    lives--;
                    if (lives == 0) {
                        auto file = std::fstream("../saves/BestScores.txt", std::ios::out | std::ios::app);
                        if (score!=0) {
                            fmt::print(file, "{}\n", score);
                        }
                        Game::setState(GameState::GameOver);
                    }
                    livesText.setString("Lives: " + std::to_string(lives));
                    it = wordsOnScreen.erase(it);
                }
            } else {
                ++it;
            }
        }
}


//DRAWING
void GamePlay::draw() const {
    window.draw(deadLine);
    window.draw(interfaceBox);
    window.draw(userTextInputBox);
    window.draw(txtInputBox);
    window.draw(userTextInput);
    window.draw(scoreText);
    window.draw(statsText);
    window.draw(instr);
    window.draw(livesText);
    for (const auto& word : wordsOnScreen) {
        window.draw(word.getText());
        if (highlight) {
            window.draw(word.getHighlightedText());
        }

    }
}


//REWRITING ARRAY OF WORDS WITH SIZES THAT WERE CHOSEN
void GamePlay::getWordsFull(const int value){
    wordsNow.clear();
    for (const auto& word : wordList) {
        if (word.length() == value) {
            wordsNow.push_back(word);
        }
    }
}

//SCORE COUNTER
void GamePlay::scoreCounter(std::string word, const float spRate) {
    int wordLength = word.length();
    int multiplier = 0;
    if (spRate >= 5) {
        multiplier = 1;
    }else if (spRate <= 4.5 && spRate > 2 ) {
        multiplier = 2;
    }else{
        multiplier = 3;
    }
    score += wordLength * multiplier;
    scoreText.setString("Score: " + std::to_string(score));
};

//UPDATES

void  GamePlay::updateFont(const sf::Font& newFont) {
    fontT = newFont;
    newFontOutOfBorders();
};
void  GamePlay::updateColors(const sf::Color newWColor, const sf::Color newWHColor) const {
    colorTxt = newWColor;
    colorTxtHoover = newWHColor;
};
void  GamePlay::updateSpawnRate(const float newSpawnRate) {
    spawnRate = newSpawnRate;
};
void  GamePlay::updateLives(const int newLives) {
    lives = newLives;
    livesText.setString("Lives: " + std::to_string(lives));
};

int GamePlay::livesValueChanged() const {
    return lives;
};
void  GamePlay::updateCSize(const int newCSize) {
    cSize = newCSize;
};
void  GamePlay::updateHighlight(const bool newHighlight) {
    highlight = newHighlight;
};
void GamePlay::updateWordSize(const int newWordSize) {
    wordSize = newWordSize;
    getWordsFull(newWordSize);
};

std::string GamePlay::getGameOverScore() {
return scoreText.getString();
}

std::string GamePlay::getGameOverWords() const {
return statsText.getString();
};
std::string GamePlay::getGameOverLastWord() const {
    if (lastWord.empty()) {
        return "Last word: none:(";
    }else{
        return "Last word: " + lastWord;
    }
};
void GamePlay::themeChanged() {
    for (WordEntity& word : wordsOnScreen) {
        word.setColor(colorTxt);
    }

    interfaceBox.setFillColor(colorTxtHoover);
    interfaceBox.setOutlineColor(colorTxt);

    userTextInputBox.setFillColor(colorTxtHoover);
    userTextInputBox.setOutlineColor(colorTxt);

    userTextInput.setFillColor(colorTxt);

    livesText.setFillColor(colorTxt);

    statsText.setFillColor(colorTxt);

    instr.setFillColor(colorTxt);

    txtInputBox.setFillColor(colorTxt);

    scoreText.setFillColor(colorTxt);
}

void GamePlay::macCheck() {
#if defined(__APPLE__) && defined(__MACH__)
    instr.setString("For cleaning input: \"Return\"\nTo clean previous char: \"Delete\"");
    scoreText.setPosition({window.getPosition().x + window.getSize().x/2.f,50});
#endif
}

