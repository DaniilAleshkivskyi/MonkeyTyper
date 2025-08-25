#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../helpers/CenterEntity.hpp"
#include "../../GameStates/IGameState.hpp"

class BestScoresMenu : public IGameState{

public:
    BestScoresMenu(sf::RenderWindow& win);

    sf::RenderWindow& window;
    sf::Font& font;
    sf::Color& colorButt;
    sf::Color& colorTxt;
    void draw() override;
    void update(const sf::Event& event) override;
    void init() override;
    void setDefColor() override;

    std::string bestScoresPath;

    std::vector<int> bestScoresList;
    std::vector<sf::RectangleShape> bestScoresShapes;
    std::vector<sf::Text> bestScoresText;
    std::vector<sf::Text> bestScoresNum;
    sf::Text emptyScores;

    void bestScoresSearcher(std::string& bestScoresPath,
                        std::vector<int>& bestScoresList,
                        sf::Color& colorButt,sf::Color& colorTxt,
                        std::vector<sf::RectangleShape>& bestScoresShapes,
                        sf::Font &font,sf::RenderWindow& window,
                        std::vector<sf::Text>& bestScoresText,
                        std::vector<sf::Text>& bestScoresNum);

};
