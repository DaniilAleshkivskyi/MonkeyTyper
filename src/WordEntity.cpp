#include "WordEntity.hpp"

sf::Font WordEntity::fontT;
std::string WordEntity::typedPart;
int WordEntity::charSize;
sf::Color WordEntity::colorT;
bool WordEntity::isHighlighted;


WordEntity::WordEntity(const std::string& word, const sf::Font& font, int charSizeC, sf::Color color, sf::Vector2f pos, float moveSpeed,bool highlight)
    : text(font,word,charSizeC),fullWord(word), speed(moveSpeed), position(pos),highlightText(font,"",charSizeC){

    text.setFillColor(color);
    text.setPosition(pos);

    isHighlighted = highlight;

    highlightText.setFillColor(sf::Color::Yellow);
    highlightText.setPosition(pos);
}




void WordEntity::updateHighlight() {
    if (typedPart.empty()) {
        highlightText.setString("");
        return;
    }

    if (fullWord.rfind(typedPart, 0) == 0) {
        highlightText.setString(typedPart);
        highlightText.setPosition(text.getPosition());
    } else {
        highlightText.setString("");
    }
}


bool WordEntity::isFullyTyped() const {
    return typedPart == fullWord;
}