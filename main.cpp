#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>


#include "src/helpers/CenterEntity.hpp"
#include "src/GameState.hpp"
#include "src/IOIteractions/MouseIteraction.hpp"
#include "src/helpers/PlaceChooseMenu.hpp"
#include "src/Configuration/ConfigOption.hpp"
#include "src/Configuration/ConfigClick.hpp"
#include "src/GamePlay/GamePlay.hpp"


void bestScoresSearcher(std::string& bestScoresPath,std::vector<int>& bestScoresList,sf::Color& colorButt,sf::Color& colorTxt, std::vector<sf::RectangleShape>& bestScoresShapes,sf::Font &font,sf::RenderWindow& window,std::vector<sf::Text>& bestScoresText,std::vector<sf::Text>& bestScoresNum);

int main() {
    using namespace sf;
    auto window = RenderWindow(
      VideoMode(VideoMode::getDesktopMode()),
        "Monkey Typer",
        Style::Close,
        State::Fullscreen,
        ContextSettings{.antiAliasingLevel = 8}
    );
    Font font;
    if (!font.openFromFile("../assets/fonts/Exo2-Regular.ttf")) {
        return -1;
    }

    /*-----------------------------------------------------*MAIN MENU *---------------------------------------------------------------*/

    Text nameText = Text(font,"Monkey Typer",90);
    nameText.setFillColor(Color(255,221,178));
    nameText.setOrigin({nameText.getLocalBounds().size.x/2.f,nameText.getLocalBounds().size.y/2.f});
    nameText.setPosition(Vector2f(window.getSize().x/2.f,window.getSize().y/2.f- 300.f));


    //BUTTONS
    //size for buttons
    Vector2f buttSize = {400,50};

    std::vector<RectangleShape> menuButtons = {
        RectangleShape (buttSize),//0
        RectangleShape(buttSize),//1
        RectangleShape(buttSize),//2
        RectangleShape(buttSize),//3
    };

    //color for our butts
    Color colorButt =  Color(176, 48, 82);
    Color hooverButt = Color(255,221,178);

    //Coloring Buttons
    for (auto& butt: menuButtons) {
        butt.setFillColor(colorButt);
        butt.setOutlineColor(hooverButt);
        butt.setOutlineThickness(5);
    }


    //centring butts with CenterVecEnt
    CenterVecEnt::RectSetVecCentre(menuButtons,window,25);



    //TEXT
    //size for txt
    int charSizeButt = 40;


    //creating Text
    std::vector<Text> menuTexts = {
        Text(font,"START GAME", charSizeButt),
        Text(font,"Best Results", charSizeButt),
        Text(font,"Settings", charSizeButt),
        Text(font,"Quit", charSizeButt),
    };


    //centring Text in butts with CenterVecEnt
    CenterVecEnt::RectSpTextCentre(menuTexts,menuButtons,window);



    //color for our text
    Color colorTxt = hooverButt;
    Color colorTxtHoover = colorButt;



    //Coloring Text
    for (auto& vec_text: menuTexts) {
        vec_text.setFillColor(colorTxt);
    }



    //Changing game mode to Main menu when entering
    GameState state = GameState::MainMenu;
    /*--------------------------------------------------*END MAIN MENU*---------------------------------------------------------------*/


    /*--------------------------------------------------*CONFIGURATION MENU*---------------------------------------------------------------*/


    Color defaultBackgroundColor = Color(215, 108, 130);

    Color wordsColor = Color::Black;
    bool isWordsColorChanged = false;


    int wordSizeMin = 1;
    int wordSizeNow = 3;
    int wordSizeMax = 10;

    int charSizeMin = 10;
    int charSizeNow = 30;
    int charSizeMax = 40;


    int livesMin = 1;
    int livesNow = 3;
    int livesMax = 10;

    float wordSpawnMin = 0.2;
    float wordSpawnNow = 2;
    float wordSpawnMax = 10;

    bool isHighlighted = true;


    Font font2;
    Font font3;
    Font font4;
    Font font5;
    Font font6;

    if (!font2.openFromFile("../assets/fonts/DynaPuff-Regular.ttf")) {
        return -1;
    }
    if (!font3.openFromFile("../assets/fonts/AlfaSlabOne-Regular.ttf")) {
        return -1;
    }
    if (!font4.openFromFile("../assets/fonts/Caveat-Regular.ttf")) {
        return -1;
    }
    if (!font5.openFromFile("../assets/fonts/LondrinaShadow-Regular.ttf")) {
        return -1;
    }
    if (!font6.openFromFile("../assets/fonts/EagleLake-Regular.ttf")) {
        return -1;
    }




    std::vector<ConfigOption> configOptions;

    // ---------- Colors ----------
    std::map<std::string, Color> colorMap = {
        {"Default(Pink)", defaultBackgroundColor},
        {"Grey",Color(169,169,169)},
        {"Black", Color::Black},
        {"White", Color::White},
        {"Yellow", Color::Yellow},
        {"Green",Color::Green},
        {"Magenta",Color::Magenta},
        {"Red",Color::Red}
    };

    Color colorNow = colorMap["Default(Pink)"];

    // ---------- Fonts ----------
    std::map<std::string, Font> fontMap = {
        {"Exo2",font},
        {"DynaPuff",font2},
        {"AlfaSlabOne",font3},
        {"Caveat",font4},
        {"LondrinaShadow",font5},
        {"EagleLake",font6}
    };

    // ---------- TEMPLATES ----------
    RectangleShape buttonTemplate({900,100});
    Text labelTemplate = Text(font,"",charSizeNow);
    labelTemplate.setCharacterSize(charSizeNow);

    // ---------- Font ----------
    labelTemplate.setString("Font");
    configOptions.emplace_back(buttonTemplate, labelTemplate, font, fontMap,Keyboard::Key::F11,Keyboard::Key::F12);


    // ---------- Background color ----------
    labelTemplate.setString("Background Color");
    configOptions.emplace_back(buttonTemplate, labelTemplate, colorMap.at("Default(Pink)"),colorMap,Keyboard::Key::F9,Keyboard::Key::F10,BgColor);

    // ---------- Word color ----------
    labelTemplate.setString("Words Color");
    configOptions.emplace_back(buttonTemplate, labelTemplate, colorMap.at("Black"), colorMap,Keyboard::Key::Num1,Keyboard::Key::Num2,TxtColor);

    // ---------- Float (spawn rate) ----------
    labelTemplate.setString("Spawn Frequency");
    configOptions.emplace_back(buttonTemplate, labelTemplate, wordSpawnNow, wordSpawnMin, wordSpawnMax,Keyboard::Key::F3,Keyboard::Key::F4);

    // ---------- Int (word size min/max) ----------
    labelTemplate.setString("Word Size");
    configOptions.emplace_back(buttonTemplate, labelTemplate, wordSizeNow, wordSizeMin, wordSizeMax,Keyboard::Key::F7,Keyboard::Key::F8,WordSize);
    // ---------- Int (char size min/max)
    labelTemplate.setString("Char Size");
    configOptions.emplace_back(buttonTemplate, labelTemplate, charSizeNow, charSizeMin, charSizeMax,Keyboard::Key::F1,Keyboard::Key::F2,CSize);
    // ---------- Int lives ----------
    labelTemplate.setString("Lives");
    configOptions.emplace_back(buttonTemplate, labelTemplate, livesNow, livesMin, livesMax,Keyboard::Key::F5,Keyboard::Key::F6,Lives);

    // ---------- Bool ----------
    labelTemplate.setString("Highlight Text");
    configOptions.emplace_back(buttonTemplate, labelTemplate, isHighlighted,Keyboard::Key::Equal,Keyboard::Key::Backslash);

    ChooseMenu::ConfOptionVecLeft(configOptions,window,25);


    bool isClicked = false;



    RectangleShape startButt({300,100});

    startButt.setFillColor(Color(0,0,0,40));
    startButt.setOutlineColor(Color::Black);
    startButt.setOutlineThickness(2);

    Text startText = Text(font,"START",charSizeNow);
    startText.setFillColor(wordsColor);

    startButt.setPosition({
        window.getSize().x - startButt.getSize().x - 40.f,
        window.getSize().y - startButt.getSize().y - 40.f
    });
    CenterEnt::RectSpTextCentre(startText,startButt,window);




    /*--------------------------------------------------*END CONFIGURATION MENU*---------------------------------------------------------------*/




    /*-----------------------------------------------------*BEST SCORES*---------------------------------------------------------------*/

    std::string bestScoresPath = "../saves/BestScores.txt";

    std::vector<int> bestScoresList;
    bool scoresOpen = false;
    std::vector<RectangleShape> bestScoresShapes;
    std::vector<Text> bestScoresText;
    std::vector<Text> bestScoresNum;
    Text emptyScores(font,"NO SCORES FOUND :(",70);
    emptyScores.setFillColor(colorTxt);
    emptyScores.setOrigin({emptyScores.getLocalBounds().size.x/2.f,emptyScores.getLocalBounds().size.y/2.f});
    emptyScores.setPosition({window.getSize().x/2.f,window.getSize().y/2.f,});
    bestScoresSearcher(bestScoresPath,bestScoresList,colorButt,colorTxt,bestScoresShapes,font,window,bestScoresText,bestScoresNum);


    /*--------------------------------------------------*END OF BEST SCORES*---------------------------------------------------------------*/
    /*--------------------------------------------------------*GAMEPLAY*-----------------------------------------------------------------------*/

    std::vector<std::string> wordList;
    auto file = std::fstream("../words.txt");
    auto word = std::string();

    while (file >> word) {
        wordList.push_back(word);
    }


    std::string userInput;
    Clock deltaClock;
    GamePlay gamePlay(window,wordList);

    /*-----------------------------------------------------*PAUSE*---------------------------------------------------------------*/
    bool justExitedPause  = false;
    IsPaused isPaused = IsPaused::Unpaused;
    //Overlay for pause
    RectangleShape pauseOverlay;
    pauseOverlay.setSize(Vector2f(window.getSize()));
    pauseOverlay.setFillColor(Color(0, 0, 0,140));

    //BUTT PAUSE
    std::vector<RectangleShape> vecButtPause = {
        RectangleShape(buttSize),//0
        RectangleShape(buttSize),//1
        RectangleShape(buttSize)//2
    };

    //Coloring butts
    for (auto& vec_butt: vecButtPause) {
        vec_butt.setOutlineColor(hooverButt);
        vec_butt.setOutlineThickness(5);
        vec_butt.setFillColor(colorButt);
    }
    //Centring them
    CenterVecEnt::RectSetVecCentre(vecButtPause,window,25);

    //TEXT PAUSE
    std::vector<Text> vecTextPause = {
        Text (font,"Resume", charSizeButt),
        Text(font,"Settings", charSizeButt),
        Text(font,"Quit", charSizeButt),
    };

    //Centring text
    CenterVecEnt::RectSpTextCentre(vecTextPause,vecButtPause,window);
    /*-----------------------------------------------------*END OF PAUSE*---------------------------------------------------------------*/


    /*--------------------------------------------------*GAMEOVER*---------------------------------------------------------------*/


    RectangleShape gameOverOverlay;
    gameOverOverlay.setSize(Vector2f(window.getSize()));
    gameOverOverlay.setFillColor(Color(0, 0, 0,140));

    Text gameOverText(font,"GAME OVER",90);
    gameOverText.setFillColor(Color(255,221,178));
    gameOverText.setOrigin({gameOverText.getLocalBounds().size.x/2.f,gameOverText.getLocalBounds().size.y/2.f});
    gameOverText.setPosition(Vector2f(window.getSize().x/2.f,window.getSize().y/2.f- 300.f));


    Text gameOverScore(font,"T",50);
    gameOverScore.setFillColor(colorTxt);

    gameOverScore.setPosition({30, window.getSize().y/2.f });

    Text gameOverWords(font,"T",50);
    gameOverWords.setFillColor(colorTxt);
    gameOverWords.setPosition({gameOverScore.getPosition().x,gameOverScore.getPosition().y + 60});


    Text gameOverLastWord(font,"T",50);
    gameOverLastWord.setFillColor(colorTxt);
    gameOverLastWord.setPosition({gameOverWords.getPosition().x,gameOverWords.getPosition().y + 60});




    //BUTT GAMEOVER
    std::vector<RectangleShape> vecButtGameOver = {
        RectangleShape(buttSize),//0
        RectangleShape(buttSize),//1
        RectangleShape(buttSize)//2
    };

    //Coloring butts
    for (auto& vec_butt: vecButtGameOver) {
        vec_butt.setOutlineColor(hooverButt);
        vec_butt.setOutlineThickness(5);
        vec_butt.setFillColor(colorButt);
    }
    //Centring them
    CenterVecEnt::RectSetVecCentre(vecButtGameOver,window,25);

    //TEXT GAMEOVER
    std::vector<Text> vecTextGameOver = {
        Text (font,"Try Again", charSizeButt),
        Text(font,"Main Menu", charSizeButt),
        Text(font,"Quit", charSizeButt),
    };

    //Centring text
    CenterVecEnt::RectSpTextCentre(vecTextGameOver,vecButtGameOver,window);



    /*--------------------------------------------------*END OF GAMEOVER*---------------------------------------------------------------*/




    while (window.isOpen()) {
        while (auto const event = window.pollEvent()) {


            if (event->is<Event::Closed>()){
                window.close();
            }
            /*-----------------------------------------------------*MEIN MENU*---------------------------------------------------------------*/
            if (state == GameState::MainMenu) {
                if (justExitedPause ) {
                    justExitedPause = false;
                    break;
                }
                //mouse iter
                if (auto const e = event->getIf<Event::MouseButtonPressed>()) {
                    if (e->button == Mouse::Button::Left) {
                        if (MouseIter::leftMousewasClicked(window, menuButtons[0])) {
                            state = GameState::ConfigurationMenu;
                        }
                        if (MouseIter::leftMousewasClicked(window, menuButtons[1])) {
                            scoresOpen = true;
                            state = GameState::BestScores;
                        }
                        if (MouseIter::leftMousewasClicked(window, menuButtons[2])) {
                            state = GameState::Settings;
                        }
                        if (MouseIter::leftMousewasClicked(window, menuButtons.back())) {
                            window.close();
                        }
                    }
                }
                //mouse hoover
                for (int i = 0; i < menuButtons.size(); ++i) {
                    auto& butt = menuButtons[i];
                    auto& txt = menuTexts[i];

                    if (MouseIter::mouseHoover(window, butt)) {
                        butt.setFillColor(hooverButt);
                        butt.setOutlineColor(colorButt);
                        txt.setFillColor(colorTxtHoover);
                    } else {
                        butt.setFillColor(colorButt);
                        butt.setOutlineColor(hooverButt);
                        txt.setFillColor(colorTxt);
                    }
                }


                //KEYBOARD
                if (auto const e = event->getIf<Event::KeyPressed>()) {
                    if (e->code == Keyboard::Key::Escape) {
                        window.close();
                    }
                }


            }
            /*-----------------------------------------------------*CONFIGMENU/SETTINGS*---------------------------------------------------------------*/
            if ( state == GameState::ConfigurationMenu||state == GameState::Settings || state == GameState::Gameplay || isPaused == IsPaused::SettingsPaused) {
                if (state == GameState::ConfigurationMenu || state == GameState::Settings) {
                    if (auto const e = event->getIf<Event::KeyPressed>()) {
                        if (e->code == Keyboard::Key::Escape) {
                            state = GameState::MainMenu;
                        }
                    }
                }

                auto const e = event->getIf<Event::KeyPressed>();

                if (isButtonPressed(Mouse::Button::Left) || e){
                    if (!isClicked) {
                        for (auto& opt : configOptions) {
                            bool doInc = ConfigClick::leftMouseRightBWasClicked(window, opt) || (e && opt.isIncPressed(*e));
                            bool doDec = ConfigClick::leftMouseLeftBWasClicked(window, opt) || (e && opt.isDecPressed(*e));
                            if (doDec){
                                switch (opt.configOptionType) {
                                    case Lives: {
                                        livesNow = opt.updateIntValue(gamePlay.livesValueChanged() - 1);
                                        gamePlay.updateLives(livesNow);
                                        break;
                                    }
                                    case WordSize: {
                                        wordSizeNow = opt.updateIntValue(opt.getIntValue() - 1);
                                        gamePlay.updateWordSize(wordSizeNow);
                                        break;
                                    }
                                    case Float: {
                                        wordSpawnNow = opt.updateFloatValue(opt.getFloatValue() - 0.5f);
                                        gamePlay.updateSpawnRate(wordSpawnNow);
                                        break;
                                    }
                                    case Bool:  {
                                        isHighlighted = opt.updateBoolValue(!opt.getBoolValue());
                                        gamePlay.updateHighlight(isHighlighted);
                                        break;
                                    }
                                    case CSize: {
                                        charSizeNow = opt.updateCSizeValue(opt.getCSizeVal() - 1);
                                        for (auto& i : configOptions) {
                                            i.update();
                                        }
                                        gamePlay.updateCSize(charSizeNow);
                                        break;
                                    }
                                    case BgColor: {
                                        colorNow = opt.prevColor();
                                        break;
                                    }
                                    case TxtColor: {
                                        wordsColor = opt.prevColor();
                                        isWordsColorChanged = true;
                                        for (auto& i : configOptions) {
                                            if (i.configOptionType != TxtColor) {
                                                i.update();
                                            }
                                        }
                                        gamePlay.updateWordColor(wordsColor);
                                        break;
                                    }
                                    case FontT: {
                                        font = opt.prevFont();
                                        for (auto& i : configOptions) {
                                            if (i.configOptionType != FontT) {
                                                i.update();

                                            }
                                        }
                                        gamePlay.updateFont(font);
                                        break;
                                    }
                                }
                            }

                            if (doInc) {
                                switch (opt.configOptionType) {
                                    case Lives: {
                                        livesNow = opt.updateIntValue(gamePlay.livesValueChanged() + 1);
                                        gamePlay.updateLives(livesNow);
                                        break;
                                    }
                                    case WordSize: {
                                        wordSizeNow = opt.updateIntValue(opt.getIntValue() + 1);
                                        gamePlay.updateWordSize(wordSizeNow);
                                        break;
                                    }
                                    case Float: {
                                        wordSpawnNow = opt.updateFloatValue(opt.getFloatValue() + 0.5f);
                                        gamePlay.updateSpawnRate(wordSpawnNow);
                                        break;
                                    }
                                    case Bool: {
                                        isHighlighted = opt.updateBoolValue(!opt.getBoolValue());
                                        gamePlay.updateHighlight(isHighlighted);
                                        break;
                                    }
                                    case CSize: {
                                        charSizeNow = opt.updateCSizeValue(opt.getCSizeVal() + 1);
                                        for (auto& i : configOptions) {
                                            i.update();
                                        }
                                        gamePlay.updateCSize(charSizeNow);
                                        break;
                                    }
                                    case BgColor: {
                                        colorNow = opt.nextColor();
                                        break;
                                    }
                                    case TxtColor: {
                                        wordsColor = opt.nextColor();
                                        isWordsColorChanged = true;
                                        for (auto& i : configOptions) {
                                            if (i.configOptionType != TxtColor) {
                                                i.update();
                                            }
                                        }
                                        gamePlay.updateWordColor(wordsColor);
                                        break;
                                    }
                                    case FontT: {
                                        font = opt.nextFont();
                                        for (auto& i : configOptions) {
                                            if (i.configOptionType != FontT) {
                                                i.update();
                                            }
                                        }
                                        gamePlay.updateFont(font);
                                        break;
                                    }

                                }
                            }
                            ChooseMenu::updateVecs(configOptions);
                        }
                        isClicked = true;
                    }
                } else {
                    isClicked = false;
                }
                if (MouseIter::leftMousewasClicked(window,startButt)) {
                    gamePlay.updateParams(font,wordsColor,wordSpawnNow,livesNow,wordSizeNow,charSizeNow,isHighlighted);
                    state = GameState::Gameplay;
                }

            }
            /*-----------------------------------------------------*GAMEPLAY*---------------------------------------------------------------*/
            if (state == GameState::Gameplay) {

                if (isPaused == IsPaused::Paused||isPaused == IsPaused::Unpaused) {
                    if (auto const e = event->getIf<Event::KeyPressed>()) {
                        if (e->code == Keyboard::Key::Escape) {
                            isPaused = (isPaused == IsPaused::Unpaused) ? IsPaused::Paused : IsPaused::Unpaused;
                        }
                    }
                }else{
                    //For pause params
                    if (auto const e = event->getIf<Event::KeyPressed>()) {
                        if (e->code == Keyboard::Key::Escape) {
                            isPaused = IsPaused::Paused;
                        }
                    }
                }



                if (isPaused == IsPaused::Paused) {
                    for (int i = 0; i < vecButtPause.size(); ++i) {
                        auto& butt = vecButtPause[i];
                        auto& txt = vecTextPause[i];

                        if (MouseIter::mouseHoover(window, butt)) {
                            butt.setFillColor(hooverButt);
                            butt.setOutlineColor(colorButt);
                            txt.setFillColor(colorTxtHoover);
                        } else {
                            butt.setFillColor(colorButt);
                            butt.setOutlineColor(hooverButt);
                            txt.setFillColor(colorTxt);
                        }
                    }

                    if (MouseIter::leftMousewasClicked(window,vecButtPause[0])) {
                        isPaused = IsPaused::Unpaused;
                    }
                    if (MouseIter::leftMousewasClicked(window,vecButtPause[1])) {
                        isPaused = IsPaused::SettingsPaused;
                    }
                    if (MouseIter::leftMousewasClicked(window,vecButtPause.back())) {
                        gamePlay.reset();
                        isPaused = IsPaused::Unpaused;
                        justExitedPause = true;
                        state = GameState::MainMenu;
                    }
                    }else if (isPaused == IsPaused::Unpaused){
                        gamePlay.handleInput(*event);
                    }
            }
            if (state == GameState::GameOver) {
                if (MouseIter::leftMousewasClicked(window,vecButtGameOver[0])) {
                    gamePlay.updateParams(font,wordsColor,wordSpawnNow,livesNow,wordSizeNow,charSizeNow,isHighlighted);
                    state = GameState::Gameplay;
                }
                if (MouseIter::leftMousewasClicked(window,vecButtGameOver[1])) {
                    justExitedPause = true;
                    state = GameState::MainMenu;
                }
                if (MouseIter::leftMousewasClicked(window,vecButtPause.back())) {
                  window.close();
                }



                for (int i = 0; i < vecButtGameOver.size(); ++i) {
                    auto& butt = vecButtGameOver[i];
                    auto& txt = vecTextGameOver[i];

                    if (MouseIter::mouseHoover(window, butt)) {
                        butt.setFillColor(hooverButt);
                        butt.setOutlineColor(colorButt);
                        txt.setFillColor(colorTxtHoover);
                    } else {
                        butt.setFillColor(colorButt);
                        butt.setOutlineColor(hooverButt);
                        txt.setFillColor(colorTxt);
                    }
                }
            }
            /*-----------------------------------------------------*BEST SCORES*---------------------------------------------------------------*/
            if (state == GameState::BestScores) {
                if (scoresOpen) {
                    bestScoresSearcher(bestScoresPath,bestScoresList,colorButt,colorTxt,bestScoresShapes,font,window,bestScoresText,bestScoresNum);
                    scoresOpen = false;
                }
                if (auto const e = event->getIf<Event::KeyPressed>()) {
                    if (e->code == Keyboard::Key::Escape) {
                        state = GameState::MainMenu;
                    }
                }
            }
        }


        /*-----------------------------------------------------*GAMEPLAY MOVING ETC.*---------------------------------------------------------------*/
            float dt = deltaClock.restart().asSeconds();
            if (state == GameState::Gameplay) {
                if (isPaused == IsPaused::Unpaused) {
                    state = gamePlay.update(dt);
                    if (state == GameState::GameOver) {
                        gameOverScore.setString(gamePlay.getGameOverScore());
                        gameOverWords.setString(gamePlay.getGameOverWords());
                        gameOverLastWord.setString(gamePlay.getGameOverLastWord());
                        gamePlay.reset();
                    }
                }
            }


        /*--------------------------------------------------*DRAWING*---------------------------------------------------------------*/
            window.clear(colorNow);


            if (state == GameState::MainMenu) {
                window.draw(nameText);
                for (auto& shape :menuButtons ) {
                    window.draw(shape);
                }
                for (auto& text :menuTexts) {
                    window.draw(text);
                }
            }
            if (state == GameState::ConfigurationMenu) {
                if (isWordsColorChanged) {
                    startText.setFillColor(wordsColor);
                    isWordsColorChanged = false;
                }

                window.draw(startButt);
                window.draw(startText);
                for (const auto& opt : configOptions) {
                   opt.draw(window);
                }
            }
            if (state == GameState::Gameplay) {
                if (isPaused == IsPaused::Unpaused||isPaused == IsPaused::Paused) {
                    gamePlay.draw();
                }

                if (isPaused == IsPaused::Paused) {
                    window.draw(pauseOverlay);
                    for (auto& shape :vecButtPause ) {
                        window.draw(shape);
                    }
                    for (auto& text :vecTextPause ) {
                        window.draw(text);
                    }
                }

                if (isPaused == IsPaused::SettingsPaused) {
                    if (isWordsColorChanged) {
                        startText.setFillColor(wordsColor);
                        isWordsColorChanged = false;
                    }
                    for (const auto& opt : configOptions) {
                        opt.draw(window);
                    }
                }
            }

        if (state == GameState::GameOver) {
            window.draw(gameOverOverlay);
            window.draw(gameOverText);
            window.draw(gameOverScore);
            window.draw(gameOverWords);
            window.draw(gameOverLastWord);
            for (auto& shape :vecButtGameOver) {
                window.draw(shape);
            }
            for (auto& text :vecTextGameOver ) {
                window.draw(text);
            }
        }


        if (state == GameState::Settings) {
            if (isWordsColorChanged) {
                startText.setFillColor(wordsColor);
                isWordsColorChanged = false;
            }
            for (const auto& opt : configOptions) {
                opt.draw(window);
            }
        }

            if (state == GameState::BestScores) {
                if (bestScoresList.empty()) {
                    window.draw(emptyScores);
                }else{
                    for (auto& shape :bestScoresShapes) {
                        window.draw(shape);
                    }
                    for (auto& text :bestScoresText) {
                        window.draw(text);
                    }
                    for (auto& text :bestScoresNum) {
                        window.draw(text);
                    }
                }

            }




            window.display();
    }
}




void bestScoresSearcher(std::string& bestScoresPath,std::vector<int>& bestScoresList,sf::Color& colorButt,sf::Color& colorTxt, std::vector<sf::RectangleShape>& bestScoresShapes,sf::Font &font,sf::RenderWindow& window,std::vector<sf::Text>& bestScoresText,std::vector<sf::Text>& bestScoresNum){
//cleaning old scores for not doubling em
    bestScoresList.clear();
    bestScoresShapes.clear();
    bestScoresText.clear();
    bestScoresNum.clear();

    using namespace sf;
    if (!std::filesystem::exists(bestScoresPath)) {
        std::ofstream createFile(bestScoresPath);
    }else{
        auto scoresFile = std::fstream(bestScoresPath);
        int sNum = 0;


        while (scoresFile >> sNum) {
            bestScoresList.push_back(sNum);
        }
    }
    if (!bestScoresList.empty()) {

        std::sort(bestScoresList.begin(),bestScoresList.end(),std::greater());

        RectangleShape templt({1000,100});
        for (auto i = 0; i < bestScoresList.size(); i++) {
            RectangleShape templt = RectangleShape({1000,100});
            templt.setFillColor(colorButt);
            templt.setOutlineThickness(2);
            templt.setOutlineColor(colorTxt);
            bestScoresShapes.push_back(templt);
            Text txtTmplt = Text(font,std::to_string(bestScoresList[i]),40);
            txtTmplt.setFillColor(colorTxt);
            bestScoresText.push_back(txtTmplt);
        }



        CenterVecEnt::RectSetVecCentre(bestScoresShapes,window,25);
        CenterVecEnt::RectSpTextCentre(bestScoresText,bestScoresShapes,window);


        for (auto i = 0; i < bestScoresList.size(); i++) {
            Text score = Text(font,std::to_string(i+1)+".",40);
            score.setFillColor(colorTxt);
            auto bounds = score.getLocalBounds();
            score.setOrigin(bounds.position + bounds.size / 2.f);
            score.setPosition({bestScoresShapes[i].getPosition().x + 30.f, bestScoresShapes[i].getPosition().y + bestScoresShapes[i].getSize().y / 2.f});
            bestScoresNum.push_back(score);
        }
    }
}
