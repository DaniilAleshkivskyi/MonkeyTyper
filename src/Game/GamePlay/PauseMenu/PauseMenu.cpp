#include "PauseMenu.hpp"
#include "../../Game.hpp"

PauseMenu::PauseMenu(sf::RenderWindow &newWindow) : window(newWindow),
                                                    font(Game::getFont()),
                                                    colorButt(Game::colorButt),hooverButt(Game::hooverButt),
                                                    colorTxt(hooverButt),hooverText(colorButt),
                                                    buttSize(Game::buttSize),charSizeButt(40),
                                                    vecButtPause{
                                                        sf::RectangleShape(buttSize),//0
                                                        sf::RectangleShape(buttSize),//1
                                                        sf::RectangleShape(buttSize)//2
                                                    },
                                                    vecTextPause{
                                                        sf::Text (font,"Resume", charSizeButt),
                                                        sf::Text(font,"Settings", charSizeButt),
                                                        sf::Text(font,"Quit", charSizeButt),
                                                    }{}

void PauseMenu::init() {
    pauseOverlay.setSize(sf::Vector2f(window.getSize()));
    pauseOverlay.setFillColor(sf::Color(0, 0, 0,140));
    //Coloring butts
    for (auto& vecButt: vecButtPause) {
        vecButt.setOutlineColor(hooverButt);
        vecButt.setOutlineThickness(5);
        vecButt.setFillColor(colorButt);
    }
    for (auto& vecTxt: vecTextPause) {
        vecTxt.setFillColor(colorTxt);
    }
    //Centring butts
    CenterVecEnt::RectSetVecCentre(vecButtPause,window,25);
    //Centring text
    CenterVecEnt::RectSpTextCentre(vecTextPause,vecButtPause,window);
}
void PauseMenu::update(const sf::Event& event) {
    for (int i = 0; i < vecButtPause.size(); ++i) {
            auto& butt = vecButtPause[i];
            auto& txt = vecTextPause[i];

            if (MouseIter::mouseHoover(window, butt)) {
                butt.setFillColor(hooverButt);
                butt.setOutlineColor(colorButt);
                txt.setFillColor(hooverText);
            } else {
                butt.setFillColor(colorButt);
                butt.setOutlineColor(hooverButt);
                txt.setFillColor(colorTxt);
            }
        }

        if (MouseIter::leftMousewasClicked(window,vecButtPause[0])) {
            Game::isPaused = IsPaused::Unpaused;
        }
        if (MouseIter::leftMousewasClicked(window,vecButtPause[1])) {
            Game::isPaused = IsPaused::SettingsPaused;
        }
        if (MouseIter::leftMousewasClicked(window,vecButtPause.back())) {
            Game::justExitedPause = true;
            Game::isPaused = IsPaused::Unpaused;
            Game::setState(GameState::MainMenu);
        }

}
void PauseMenu::draw() {
    window.draw(pauseOverlay);
    for (auto& shape :vecButtPause ) {
        window.draw(shape);
    }
    for (auto& text :vecTextPause ) {
        window.draw(text);
    }
}




