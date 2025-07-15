#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct WordEntity {
    sf::Text text;
    std::string fullWord;


    static sf::Font fontT;
    static sf::Color colorT;
    static int charSize;
    static bool isHighlighted;

    sf::Text highlightText;
    static std::string typedPart;

    float speed;
    sf::Vector2f position;




   WordEntity(const std::string& word, const sf::Font& font, int charSizeC, sf::Color color, sf::Vector2f pos, float moveSpeed,bool highlight);

    void updateHighlight();
    bool isFullyTyped() const;
};
