#include "Game.hpp"

using namespace sf;

Color Game::colorButt = Color(176, 48, 82);
Color Game::hooverButt = Color(255,221,178);
//size for buttons
Vector2f Game::buttSize = {400,50};
GameState Game::state = GameState::MainMenu;
IsPaused Game::isPaused = IsPaused::Unpaused;
Font Game::font = Font("../assets/fonts/Exo2-Regular.ttf");
RenderWindow Game::window;
bool Game::justExitedPause = false;
bool Game::scoresOpen = true;
Color Game::bgColor = Color::Black;

Game::Game() : mainMenu(window), gamePlay(window,wordList),configMenu(window,gamePlay), bestScoresMenu(window){



    run();
}

void Game::run() {
    window = RenderWindow(
    VideoMode(VideoMode::getDesktopMode()),
"Monkey Typer",
    Style::Close,
    State::Fullscreen,
    ContextSettings{.antiAliasingLevel = 8}
    );
    while (wordFile >> word) {
        wordList.push_back(word);
    }

    std::string userInput;


    mainMenu.init();
    bestScoresMenu.init();
    configMenu.init();
    Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        update(dt);
        draw();
    }
}



void Game::update(float dt) {
        while (auto const event = window.pollEvent()) {
            if (event->is<Event::Closed>()){
                window.close();
            }

            if (state == GameState::MainMenu) {
                if (justExitedPause) {
                    justExitedPause = false;
                    break;
                }
                mainMenu.update(*event);
            }
            if (state == GameState::BestScores) {
                bestScoresMenu.update(*event);
            }
            if ( state == GameState::ConfigurationMenu||state == GameState::Settings || state == GameState::Gameplay || isPaused == IsPaused::SettingsPaused) {
                if ( state == GameState::ConfigurationMenu || state == GameState::Settings) {
                    if (auto const e = event->getIf<Event::KeyPressed>()) {
                        if (e->code == sf::Keyboard::Key::Escape) {
                            state = GameState::MainMenu;
                        }
                    }
                }
                configMenu.update(*event);
            }
        }
}


void Game::draw() {
    window.clear(bgColor);
    switch (state) {
        case GameState::MainMenu:
            mainMenu.draw();
            break;
        case GameState::BestScores:
            bestScoresMenu.draw();
            break;
    }
    if (state == GameState::MainMenu) {
        mainMenu.draw();
    }else if (state == GameState::BestScores) {
        bestScoresMenu.draw();
    }else if (state == GameState::ConfigurationMenu||state == GameState::Settings) {
        configMenu.draw();
    }
    window.display();
}

void Game::setState(GameState newState) {
    state = newState;
}

Font& Game::getFont() {
    return font;
}
void Game::setFont(Font& newFont) {
    font = newFont;
}

RenderWindow& Game::getWindow() {
    return window;
}


 Color Game::getColorButt() {
    return colorButt;
}
Color Game::getHooverButt() {
    return hooverButt;
}
 Vector2f Game::getButtSize() {
    return buttSize;
}