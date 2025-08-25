#include "MainMenu.hpp"
#include "../Game.hpp"
using namespace sf;


MainMenu::MainMenu(RenderWindow& win)
       : font(Game::getFont()),
         window(win),
         colorButt(Game::getColorButt()),
         hooverButt(Game::getHooverButt()),
         colorTxt(hooverButt),
         colorTxtHoover(colorButt),
         buttSize(Game::getButtSize()),
         nameText(font, "Monkey Typer", 90),
         monkeyTyper(monkeyTyperTexture),
         menuButtons{
             RectangleShape(buttSize),
             RectangleShape(buttSize),
             RectangleShape(buttSize),
             RectangleShape(buttSize),
         },
         menuTexts{
             Text(font,"START GAME", charSizeButt),
             Text( font,"Best Results", charSizeButt),
             Text(font,"Settings", charSizeButt),
             Text(font,"Quit",charSizeButt),
         }{};


void MainMenu::init() {
    nameText.setOutlineColor(colorButt);
    nameText.setOutlineThickness(4);
    nameText.setFillColor(colorTxt);
    nameText.setOrigin({nameText.getLocalBounds().size.x/2.f,nameText.getLocalBounds().size.y/2.f});
    nameText.setPosition(Vector2f(window.getSize().x/2.f,window.getSize().y/2.f- 300.f));

    //Coloring Buttons
    for (auto& butt: menuButtons) {
        butt.setFillColor(colorButt);
        butt.setOutlineColor(hooverButt);
        butt.setOutlineThickness(5);
    }

    //centring butts with CenterVecEnt
    CenterVecEnt::RectSetVecCentre(menuButtons,window,25);

    //centring Text in butts with CenterVecEnt
    CenterVecEnt::RectSpTextCentre(menuTexts,menuButtons,window);


    //Coloring Text
    for (auto& vec_text: menuTexts) {
        vec_text.setFillColor(colorTxt);
    }

    monkeyTyper.setPosition(nameText.getPosition());
    /*monkeyTyper.setScale({0.9f, 0.95f});*/
}


 void MainMenu::update(const Event& event) {
                 //mouse iter
                 if (auto const e = event.getIf<Event::MouseButtonPressed>()) {
                     if (e->button == Mouse::Button::Left) {
                         if (MouseIter::leftMousewasClicked(window, menuButtons[0])) {
                            Game::setState(GameState::ConfigurationMenu);
                         }
                         if (MouseIter::leftMousewasClicked(window, menuButtons[1])) {
                             Game::scoresOpen = true;
                             Game::setState(GameState::BestScores);
                         }
                         if (MouseIter::leftMousewasClicked(window, menuButtons[2])) {
                             Game::setState(GameState::Settings);
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
                 if (Game::themeChanged) {
                     nameText.setOutlineColor(colorButt);
                     nameText.setFillColor(colorTxt);
                     Game::themeChanged = false;
                 }


                 //KEYBOARD
                 if (auto const e = event.getIf<Event::KeyPressed>()) {
                     if (e->code == Keyboard::Key::Escape) {
                         window.close();
                     }
                 }
}

void MainMenu::draw(){
    window.draw(nameText);

    for (auto& shape : menuButtons) {
        window.draw(shape);
    }

    for (auto& text :menuTexts) {
        window.draw(text);
    }

    window.draw(monkeyTyper);
}


void MainMenu::setDefColor() {
    for (int i = 0; i < menuButtons.size(); ++i) {
        auto& butt = menuButtons[i];
        auto& txt = menuTexts[i];

        butt.setFillColor(colorButt);
        butt.setOutlineColor(hooverButt);
        txt.setFillColor(colorTxt);
    }
}








