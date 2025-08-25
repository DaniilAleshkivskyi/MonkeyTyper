#include "WordEntity.hpp"

#include "fmt/compile.h"

sf::Color WordEntity::txtColor;
std::string WordEntity::typedPart;
int WordEntity::charSize;
bool WordEntity::isHighlighted;


WordEntity::WordEntity(const std::string& word, const sf::Font& font, int charSizeC, sf::Color& color, sf::Vector2f pos, float moveSpeed,bool highlight)
    : text(font,word,charSizeC),fullWord(word), speed(moveSpeed), position(pos),highlightText(font,"",charSizeC){
    txtColor = color;

    text.setFillColor(txtColor);
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

void WordEntity::clearTypedPart() {
    typedPart.clear();
}
void WordEntity::setTypedPart(const std::string& typedTxt) {
    typedPart = typedTxt;
}
std::string WordEntity::getFullWord() const {
    return fullWord;
}
const sf::Text& WordEntity::getText() const{
    return text;
}
sf::Text& WordEntity::getText() {
    return text;
}
const sf::Text& WordEntity::getHighlightedText() const{
    return highlightText;
}
sf::Text& WordEntity::getHighlightedText(){
    return highlightText;
}
float WordEntity::getSpeed() const {
    return speed;
}

void WordEntity::setColor(sf::Color& color) {
    text.setFillColor(color);
}

bool WordEntity::isFullyTyped() const {
    return typedPart == fullWord;
}