#include "GameOver.hpp"
#include "../../Game.hpp"


GameOver::GameOver(sf::RenderWindow& newWindow)
:window(newWindow),font(Game::getFont()),buttSize(Game::buttSize),
gameOverText(font,"GAME OVER",90),gameOverScore(font,"T",50),gameOverWords(font,"T",50),gameOverLastWord(font,"T",50),
hooverButt(Game::hooverButt),colorButt(Game::colorButt),
vecButtGameOver{
    sf::RectangleShape(buttSize),//0
    sf::RectangleShape(buttSize),//1
    sf::RectangleShape(buttSize)//2
    },
vecTextGameOver{
    sf::Text (font,"Try Again", charSizeButt),//0
    sf::Text(font,"Main Menu", charSizeButt),//1
    sf::Text(font,"Quit", charSizeButt),//2
}{}

void GameOver::init() {
    gameOverOverlay.setSize(sf::Vector2f(window.getSize()));
    gameOverOverlay.setFillColor(sf::Color(0, 0, 0,140));


    gameOverText.setFillColor(hooverButt);
    gameOverText.setOrigin({gameOverText.getLocalBounds().size.x/2.f,gameOverText.getLocalBounds().size.y/2.f});
    gameOverText.setPosition(sf::Vector2f(window.getSize().x/2.f,window.getSize().y/2.f- 300.f));

    gameOverScore.setFillColor(hooverButt);
    gameOverScore.setPosition({30, window.getSize().y/2.f });


    gameOverWords.setFillColor(hooverButt);
    gameOverWords.setPosition({gameOverScore.getPosition().x,gameOverScore.getPosition().y + 60});


    gameOverLastWord.setFillColor(hooverButt);
    gameOverLastWord.setPosition({gameOverWords.getPosition().x,gameOverWords.getPosition().y + 60});


    for (auto& vec_butt: vecButtGameOver) {
            vec_butt.setOutlineColor(hooverButt);
            vec_butt.setOutlineThickness(5);
            vec_butt.setFillColor(colorButt);
    }

    for (auto& vec_txt: vecTextGameOver) {
        vec_txt.setFillColor(hooverButt);
    }

    CenterVecEnt::RectSetVecCentre(vecButtGameOver,window,25);

    CenterVecEnt::RectSpTextCentre(vecTextGameOver,vecButtGameOver,window);

}

void GameOver::update(const sf::Event& event) {
    if (MouseIter::leftMousewasClicked(window,vecButtGameOver[0])) {
            Game::setState(GameState::ConfigurationMenu);
    }
    if (MouseIter::leftMousewasClicked(window,vecButtGameOver[1])) {
        Game::justExitedPause = true;
        Game::setState(GameState::MainMenu);
    }
    if (MouseIter::leftMousewasClicked(window,vecButtGameOver.back())) {
        window.close();
    }
}

void GameOver::colorButts() {
    for (int i = 0; i < vecButtGameOver.size(); ++i) {
        auto& butt = vecButtGameOver[i];
        auto& txt = vecTextGameOver[i];

        if (MouseIter::mouseHoover(window, butt)) {
            butt.setFillColor(hooverButt);
            butt.setOutlineColor(colorButt);
            txt.setFillColor(colorButt);
        } else {
            butt.setFillColor(colorButt);
            butt.setOutlineColor(hooverButt);
            txt.setFillColor(hooverButt);
        }
    }
    if (Game::themeChanged) {
        gameOverText.setFillColor(hooverButt);
    }
}


void GameOver::draw() {
    window.draw(gameOverOverlay);
    window.draw(gameOverText);
    window.draw(gameOverScore);
    window.draw(gameOverWords);
    window.draw(gameOverLastWord);
    for (auto& shape :vecButtGameOver) {
        window.draw(shape);
    }
    for (auto& text :vecTextGameOver) {
        window.draw(text);
    }
}

void GameOver::setDefColor() {
    for (int i = 0; i < vecButtGameOver.size(); ++i) {
        auto& butt = vecButtGameOver[i];
        auto& txt = vecTextGameOver[i];

        butt.setFillColor(colorButt);
        butt.setOutlineColor(hooverButt);
        txt.setFillColor(hooverButt);
    }
}


void GameOver::setGameOverScore(std::string score){
    gameOverScore.setString(score);
}
void GameOver::setGameOverWords(std::string words) {
    gameOverWords.setString(words);
}
void GameOver::setGameOverLastWord(std::string lastWord) {
    gameOverLastWord.setString(lastWord);
}
