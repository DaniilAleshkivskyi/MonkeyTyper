#include "BestScoresMenu.hpp"
#include "../Game.hpp"



BestScoresMenu::BestScoresMenu(sf::RenderWindow& win): window(win),
                                  font(Game::getFont()),
                                  colorButt( Game::getColorButt()),
                                  colorTxt(Game::getHooverButt()),
                                  scoresOpen(false),
                                  emptyScores(Game::getFont(),"NO SCORES FOUND :(",70),
                                  bestScoresPath("../saves/BestScores.txt") {}

void BestScoresMenu::init() {
    emptyScores.setFillColor(colorTxt);
    emptyScores.setOrigin({emptyScores.getLocalBounds().size.x / 2.f, emptyScores.getLocalBounds().size.y / 2.f});
    emptyScores.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f,});
    bestScoresSearcher(bestScoresPath, bestScoresList, colorButt, colorTxt, bestScoresShapes, font, window,bestScoresText, bestScoresNum);
}



void BestScoresMenu::update(const sf::Event& event) {
            if (scoresOpen) {
                bestScoresSearcher(bestScoresPath,bestScoresList,colorButt,colorTxt,bestScoresShapes,font,window,bestScoresText,bestScoresNum);
                scoresOpen = false;
            }
            if (auto const e = event.getIf<sf::Event::KeyPressed>()) {
                if (e->code == sf::Keyboard::Key::Escape) {
                    Game::setState(GameState::MainMenu);
                }
            }
}
void BestScoresMenu::draw() {
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




void BestScoresMenu::bestScoresSearcher(std::string &bestScoresPath,
                                        std::vector<int> &bestScoresList,
                                        sf::Color &colorButt,
                                        sf::Color &colorTxt,
                                        std::vector<sf::RectangleShape> &bestScoresShapes,
                                        sf::Font &font,
                                        sf::RenderWindow &window,
                                        std::vector<sf::Text> &bestScoresText,
                                        std::vector<sf::Text> &bestScoresNum) {
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
