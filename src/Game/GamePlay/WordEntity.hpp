#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class WordEntity {
    sf::Text text;
    std::string fullWord;

    static sf::Color txtColor;
    static int charSize;
    static bool isHighlighted;

    sf::Text highlightText;
    static std::string typedPart;

    float speed;
    sf::Vector2f position;



public:
    WordEntity(const std::string& word, const sf::Font& font, int charSizeC, sf::Color& color, sf::Vector2f pos, float moveSpeed,bool highlight);
    static void clearTypedPart();
    void setColor(sf::Color& color);
    static void setTypedPart(const std::string& typedTxt);
    std::string getFullWord() const;
    sf::Text& getText();
    const sf::Text& getText() const;
    sf::Text& getHighlightedText();
    const sf::Text& getHighlightedText() const;
    float getSpeed() const;
    void updateHighlight();
    bool isFullyTyped() const;
};
