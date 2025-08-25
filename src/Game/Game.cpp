#include "Game.hpp"

using namespace sf;

Color Game::colorButt;
Color Game::hooverButt;
Vector2f Game::buttSize = {400,50};
GameState Game::state = GameState::MainMenu;
IsPaused Game::isPaused = IsPaused::Unpaused;
Font Game::font = Font("../assets/fonts/Exo2-Regular.ttf");
RenderWindow Game::window;
bool Game::justExitedPause = false;
bool Game::scoresOpen = true;
bool Game::gameOverStatsRefresh = true;
bool Game::themeChanged = false;
Color Game::bgColor = Color::Black;


Game::Game() : gamePlay(window,wordList),
               configMenu(window,gamePlay),
               bestScoresMenu(window),
               pauseMenu(window),
               gameOver(window),
               mainMenu(window){
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
    gamePlay.init();
    pauseMenu.init();
    gameOver.init();
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
                    gamePlay.reset();
                    justExitedPause = false;
                }
                mainMenu.update(*event);
            }
            if (state == GameState::BestScores) {
                if (auto const e = event->getIf<Event::KeyPressed>())  {
                    if (e->code == Keyboard::Key::Escape) {
                        scoresOpen = true;
                        mainMenu.setDefColor();
                        setState(GameState::MainMenu);
                    }
                }
                bestScoresMenu.update(*event);
            }
            if ( state == GameState::ConfigurationMenu || state == GameState::Settings) {
                if (auto const e = event->getIf<Event::KeyPressed>()) {
                    if (e->code == Keyboard::Key::Escape) {
                        mainMenu.setDefColor();
                        state = GameState::MainMenu;
                    }
                }
            }
            configMenu.update(*event);


            if (state == GameState::Gameplay) {
                if (isPaused == IsPaused::Paused) {
                    pauseMenu.setDefColor();
                    pauseMenu.update(*event);
                }
                if (auto const e = event->getIf<Event::KeyPressed>()) {
                    if (isPaused!=IsPaused::SettingsPaused) {
                        if (e->code == Keyboard::Key::Escape) {
                            isPaused = (isPaused == IsPaused::Unpaused) ? IsPaused::Paused : IsPaused::Unpaused;
                        }
                    }else{
                        //For SettingsPaused
                        if (e->code == Keyboard::Key::Escape) {
                            isPaused = IsPaused::Paused;
                        }
                    }
                }



                if (isPaused == IsPaused::Unpaused) {
                    gamePlay.handleInput(*event);
                }
            }
            if (state == GameState::GameOver) {
              gameOver.setDefColor();
              gameOver.update(*event);
            }
        }


    //UPDATING GAMEPLAY WHENEVER EVENT EXISTS OR NOT
    //--PollEvent returns false if there is no event,but while state == gameplay we must update it every frame

    if (state == GameState::GameOver) {
        if (gameOverStatsRefresh) {
            gameOverStatsRefresh = false;
            setGameOverStats();
        }
        gameOver.colorButts();
    }

    if (state == GameState::Gameplay && isPaused == IsPaused::Unpaused) {
        gamePlay.update(dt);
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

        case GameState::ConfigurationMenu:
        case GameState::Settings:

            configMenu.draw();
            break;

        case GameState::Gameplay:
            if (isPaused != IsPaused::SettingsPaused) {
                gamePlay.draw();
            }

            if (isPaused == IsPaused::Paused) {
                pauseMenu.draw();
            }else if (isPaused == IsPaused::SettingsPaused) {
                configMenu.draw();
            }
            break;
        case GameState::GameOver:
            gameOver.draw();
            break;
    }
    window.display();
}
void Game::setGameOverStats() {
    gameOver.setGameOverScore(gamePlay.getGameOverScore());
    gameOver.setGameOverWords(gamePlay.getGameOverWords());
    gameOver.setGameOverLastWord(gamePlay.getGameOverLastWord());
    gamePlay.reset();
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
 Color& Game::getColorButt() {
    return colorButt;
}
Color& Game::getHooverButt() {
    return hooverButt;
}
 Vector2f Game::getButtSize() {
    return buttSize;
}
GameState Game::getState() {
    return state;
}
void Game::setTheme(Theme newTheme){
    bgColor = newTheme.background;
    colorButt = newTheme.colorButt;
    hooverButt = newTheme.hooverButt;
    themeChanged = true;
}