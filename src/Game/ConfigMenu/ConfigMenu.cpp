#include "ConfigMenu.hpp"
#include "../Game.hpp"



ConfigMenu::ConfigMenu(sf::RenderWindow &win,GamePlay &gameplay):window(win),
                                              gamePlay(gameplay),
                                              font(Game::getFont()),
                                              wordsColor(),buttColl(),
                                              isHighlighted(true),isClicked(false),
                                              charSizeMin(10),charSizeNow(30),charSizeMax(40),
                                              labelTemplate(sf::Text(font,"",charSizeNow)),
                                              buttonTemplate({900,100}),
                                              wordSizeMin(1),wordSizeNow(3),wordSizeMax(10),
                                              livesMin(1),livesNow(3),livesMax(10),
                                              wordSpawnMin(0.2),wordSpawnNow(2),wordSpawnMax(10),
                                              colorMap({
                                                  {"PINK", Theme(sf::Color(215, 108, 130),sf::Color(176, 48, 82),sf::Color(255, 221, 178))},
                                                  {"GREEN", Theme(sf::Color(192, 199, 140),sf::Color(185, 148, 112),sf::Color(254, 250, 224))},
                                                  {"NAVY",Theme(sf::Color(34, 40, 49),sf::Color(57, 62, 70),sf::Color(148, 137, 121))},
                                                  {"BROWN",Theme(sf::Color (111, 78, 55),sf::Color (166, 123, 91),sf::Color (254, 216, 177))}}),
                                              startButt({300,100}),
                                              startText(font,"START",charSizeNow){
    if (!font2.openFromFile("../assets/fonts/DynaPuff-Regular.ttf")) {
        throw std::runtime_error("Could not open font2 file");
    }
    if (!font3.openFromFile("../assets/fonts/AlfaSlabOne-Regular.ttf")) {
        throw std::runtime_error("Could not open font3 file");
    }
    if (!font4.openFromFile("../assets/fonts/Caveat-Regular.ttf")) {
        throw std::runtime_error("Could not open font4 file");
    }
    if (!font5.openFromFile("../assets/fonts/LondrinaShadow-Regular.ttf")) {
        throw std::runtime_error("Could not open font5 file");
    }
    if (!font6.openFromFile("../assets/fonts/EagleLake-Regular.ttf")) {
        throw std::runtime_error("Could not open font6 file");
    }
    fontMap =  {
        {"Exo2",font},
        {"DynaPuff",font2},
        {"AlfaSlabOne",font3},
        {"Caveat",font4},
        {"LondrinaShadow",font5},
        {"EagleLake",font6}};
}

void ConfigMenu::init() {
    // ---------- Font ----------
    labelTemplate.setString("Font");
    configOptions.emplace_back(buttonTemplate, labelTemplate, font, fontMap,sf::Keyboard::Key::Num9,sf::Keyboard::Key::Num0);

    //------------ Theme ---------
    labelTemplate.setString("Theme");
    configOptions.emplace_back(buttonTemplate, labelTemplate,colorMap,sf::Keyboard::Key::Num1,sf::Keyboard::Key::Num2,Themes);

    // ---------- Float (spawn rate) ----------
    labelTemplate.setString("Spawn Frequency");
    configOptions.emplace_back(buttonTemplate, labelTemplate, wordSpawnNow, wordSpawnMin, wordSpawnMax,sf::Keyboard::Key::F3,sf::Keyboard::Key::F4);

    // ---------- Int (word size min/max) ----------
    labelTemplate.setString("Word Size");
    configOptions.emplace_back(buttonTemplate, labelTemplate, wordSizeNow, wordSizeMin, wordSizeMax,sf::Keyboard::Key::F7,sf::Keyboard::Key::F8,WordSize);
    // ---------- Int (char size min/max)
    labelTemplate.setString("Char Size");
    configOptions.emplace_back(buttonTemplate, labelTemplate, charSizeNow, charSizeMin, charSizeMax,sf::Keyboard::Key::F1,sf::Keyboard::Key::F2,CSize);
    // ---------- Int lives ----------
    labelTemplate.setString("Lives");
    configOptions.emplace_back(buttonTemplate, labelTemplate, livesNow, livesMin, livesMax,sf::Keyboard::Key::F5,sf::Keyboard::Key::F6,Lives);

    // ---------- Bool ----------
    labelTemplate.setString("Highlight Text");
    configOptions.emplace_back(buttonTemplate, labelTemplate, isHighlighted,sf::Keyboard::Key::Equal,sf::Keyboard::Key::Backslash);

    ChooseMenu::ConfOptionVecLeft(configOptions,window,25);

    auto t = configOptions.at(1).prevTheme();
    wordsColor = t.hooverButt;
    buttColl = t.colorButt;
    Game::setTheme(t);
    gamePlay.updateWordColor(wordsColor);
    for (auto& i : configOptions) {
        i.update();
    }


    startButt.setFillColor(sf::Color(0,0,0,40));
    startButt.setOutlineThickness(2);
    startText.setFillColor(wordsColor);
    startButt.setOutlineColor(wordsColor);
    startButt.setFillColor(buttColl);

    startButt.setPosition({
        window.getSize().x - startButt.getSize().x - 40.f,
        window.getSize().y - startButt.getSize().y - 40.f
    });
    CenterEnt::RectSpTextCentre(startText,startButt,window);
}
void ConfigMenu::update(const sf::Event& event) {
                 auto const e = event.getIf<sf::Event::KeyPressed>();

                 if (isButtonPressed(sf::Mouse::Button::Left) || e){
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
                                     case Themes: {
                                         Theme newTheme = opt.prevTheme();
                                         wordsColor = newTheme.hooverButt;
                                         buttColl = newTheme.colorButt;
                                         startText.setFillColor(wordsColor);
                                         startButt.setOutlineColor(wordsColor);
                                         startButt.setFillColor(buttColl);
                                         Game::setTheme(newTheme);
                                         gamePlay.updateWordColor(wordsColor);
                                         for (auto& i : configOptions) {
                                             i.update();
                                         }
                                         break;
                                     }
                                     case FontT: {
                                         font = opt.prevFont();
                                         for (auto& i : configOptions) {
                                             if (i.configOptionType != FontT) {
                                                 i.update();
                                             }
                                         }
                                         Game::setFont(font);
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
                                    case Themes: {
                                         Theme newTheme = opt.nextTheme();
                                         wordsColor = newTheme.hooverButt;
                                         buttColl = newTheme.colorButt;
                                         startText.setFillColor(wordsColor);
                                         startButt.setOutlineColor(wordsColor);
                                         startButt.setFillColor(buttColl);
                                         Game::setTheme(newTheme);
                                         gamePlay.updateWordColor(wordsColor);
                                         for (auto& i : configOptions) {
                                             i.update();
                                         }
                                         break;
                                     }
                                     case FontT: {
                                         font = opt.nextFont();
                                         for (auto& i : configOptions) {
                                             if (i.configOptionType != FontT) {
                                                 i.update();
                                             }
                                         }
                                         Game::setFont(font);
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


                 if (Game::getState() != GameState::Settings && Game::isPaused != IsPaused::SettingsPaused) {
                     if (MouseIter::leftMousewasClicked(window,startButt)) {
                         Game::gameOverStatsRefresh = true;
                         gamePlay.updateParams(font,wordsColor,wordSpawnNow,livesNow,wordSizeNow,charSizeNow,isHighlighted);
                         Game::setState(GameState::Gameplay);
                     }
                 }
}
void ConfigMenu::draw() {
    if (Game::getState() == GameState::ConfigurationMenu) {
        window.draw(startButt);
        window.draw(startText);
    }
    for (const auto& opt : configOptions) {
        opt.draw(window);
    }
}
void ConfigMenu::setDefColor() {}



