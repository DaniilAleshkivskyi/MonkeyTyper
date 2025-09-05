#include "ConfigOption.hpp"

#include <iostream>


std::pair<sf::RectangleShape, sf::Text> createButton(const sf::Font& font, const std::string& txt);
std::string ConfigOption::fontName;
sf::Font ConfigOption::fontValue;


float  ConfigOption::floatValue = 0;
float  ConfigOption::minFloatVal = 0;
float  ConfigOption::maxFloatVal = 0;
int ConfigOption::cSizeVal = 30;
sf::Color ConfigOption::hooverButt;
sf::Color ConfigOption::bgColor;
sf::Color ConfigOption::colorButt;
std::string ConfigOption::themeName;



//INT VALUE/CHAR SIZE
ConfigOption::ConfigOption( sf::RectangleShape& button,const sf::Text& label,int intValueE,int minIntVal,int maxIntVal,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc,ConfigOptionType cOT) //delocalise is used for converting from key type to keyScan type
:button(button),label(label), value(fontValue, "", cSizeVal),minIntVal(minIntVal),maxIntVal(maxIntVal),keyDec(keyDec),keyDecB(createButton(fontValue, "Decrease\n\t\"" + getDescription(delocalize(keyDec))+ "\"")),keyInc(keyInc),keyIncB(createButton(fontValue, "Increase\n\t\"" + getDescription(delocalize(keyInc))+ "\"")),configOptionType(cOT),leftButton(createButton(fontValue, "<")),rightButton(createButton(fontValue, ">"))  {
    if (cOT == CSize) {
        cSizeVal = intValueE;
    } else {
        intValue = intValueE;
    }
    setRectColor();
    update();
}



//FLOAT
ConfigOption::ConfigOption( sf::RectangleShape& button,const sf::Text& label,float floatValueE,float minVal,float maxVal,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc)
: button(button), label(label), value(fontValue, "", cSizeVal),configOptionType(Float),keyDec(keyDec),keyDecB(createButton(fontValue, "Decrease\n\t\"" + getDescription(delocalize(keyDec))+ "\"")),keyInc(keyInc),keyIncB(createButton(fontValue, "Increase\n\t\"" + getDescription(delocalize(keyInc))+ "\"")),leftButton(createButton(fontValue, "<")),rightButton(createButton(fontValue, ">")) {


    floatValue = floatValueE;
    minFloatVal = minVal;
    maxFloatVal = maxVal;

    setRectColor();
    update();
};

//BOOL
ConfigOption::ConfigOption( sf::RectangleShape& button,const sf::Text& label,const bool& boolValue,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc)
:button(button), label(label), value(fontValue, "", cSizeVal),boolValue(boolValue), configOptionType(Bool),keyDec(keyDec),keyDecB(createButton(fontValue, "Decrease\n\t\"" + getDescription(delocalize(keyDec))+ "\"")),keyInc(keyInc),keyIncB(createButton(fontValue, "Increase\n\t\"" + getDescription(delocalize(keyInc))+ "\"")),leftButton(createButton(fontValue, "<")),rightButton(createButton(fontValue, ">")) {
    setRectColor();
    update();
};



//THEME
ConfigOption::ConfigOption( sf::RectangleShape& button,const sf::Text& label,const std::map<std::string,Theme>& newColorMap,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc,ConfigOptionType cOT)
:button(button), label(label),colorMap(newColorMap),value(fontValue, "", cSizeVal),keyDec(keyDec),keyDecB(createButton(fontValue, "Decrease\n\t\"" + getDescription(delocalize(keyDec))+ "\"")),keyInc(keyInc),keyIncB(createButton(fontValue, "Increase\n\t\"" + getDescription(delocalize(keyInc))+ "\"")),configOptionType(cOT),leftButton(createButton(fontValue, "<")),rightButton(createButton(fontValue, ">")) {
    value.setString("PINK");
    setRectColor();
    update();
};

//FONT
ConfigOption::ConfigOption( sf::RectangleShape& button,sf::Text& label,const sf::Font& font,const std::map<std::string, sf::Font>& fontMap,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc)
    : button(button),label(label),value(font, "", cSizeVal),fontMap(fontMap),keyDec(keyDec),keyDecB(createButton(fontValue, "Decrease\n\t\"" + getDescription(delocalize(keyDec))+ "\"")),keyInc(keyInc),keyIncB(createButton(fontValue, "Increase\n\t\"" + getDescription(delocalize(keyInc))+ "\"")),configOptionType(FontT),leftButton(createButton(fontValue, "<")),rightButton(createButton(fontValue, ">")){
    auto it = fontMap.find("Exo2");
    if (it != fontMap.end()) {
        fontName = (*it).first;
        fontValue = (*it).second;
    } else {
        fontName = (*fontMap.begin()).first;
        fontValue = (*fontMap.begin()).second;
    }

    label.setFont(fontValue);
    value.setFont(fontValue);
    value.setString(fontName);

    setRectColor();
    update();

}




int ConfigOption::updateIntValue(int newValue) {
            if (newValue < minIntVal) {
                intValue = minIntVal;
            } else if (newValue > maxIntVal) {
                intValue = maxIntVal;
            } else {
                intValue = newValue;
            }
        update();
    return intValue;
}
int ConfigOption::getIntValue() const {
    return intValue;
}


float ConfigOption::updateFloatValue(float newValue) {
    if (newValue < minFloatVal) {
        newValue = minFloatVal;
    }else if (newValue > maxFloatVal) {
        newValue = maxFloatVal;
    }else {
        floatValue = newValue;
    }
    update();
    return floatValue;
}

float ConfigOption::getFloatValue() const {
    return floatValue;
}


bool ConfigOption::updateBoolValue(const bool& newValue) {
    boolValue = newValue;
    update();
    return boolValue;
};
bool ConfigOption::getBoolValue() const {
    return boolValue;
};



int ConfigOption::updateCSizeValue(int newValue) {
    if (newValue < minIntVal) {
        cSizeVal = minIntVal;
    } else if (newValue > maxIntVal) {
        cSizeVal = maxIntVal;
    } else {
        cSizeVal = newValue;
    }
    return cSizeVal;
}

void ConfigOption::updateCSize(){
    label.setCharacterSize(cSizeVal);
    value.setCharacterSize(cSizeVal);
}
int ConfigOption::getCSizeVal() {
    return cSizeVal;
}

Theme ConfigOption::nextTheme() {
    auto it = colorMap.find(themeName);
    if (it == colorMap.end()) {
        it = colorMap.begin();
    }else{
        ++it;
        if (it == colorMap.end()) {
            it = colorMap.begin();
        }
    }

    themeName = it->first;
    hooverButt = it->second.hooverButt;
    colorButt = it->second.colorButt;
    return it->second;
}

Theme ConfigOption::prevTheme() {
    auto it = colorMap.find(themeName);
    if (it == colorMap.begin()) {
        it = colorMap.end();
    }
    --it;

    themeName = it->first;
    hooverButt = it->second.hooverButt;
    colorButt = it->second.colorButt;
    return it->second;
}



std::string ConfigOption::getFontName() const {
    return fontName;
}
sf::Font  ConfigOption::getFont() const {
    return fontValue;
}

void ConfigOption::updateFontValue(const sf::Font& newValue,const std::string& newFontName){
    fontName = newFontName;
    fontValue = newValue;
    update();
}



sf::Font ConfigOption::nextFont() {
    auto it = fontMap.begin();
    for ( it;it != fontMap.end(); ++it) {
        if ((*it).first == fontName) {
            ++it;
            break;
        }
    }
    if (it == fontMap.end()) {
        it = fontMap.begin(); //going from start if in the end
    }
    updateFontValue((*it).second,(*it).first);
    return (*it).second;
}


sf::Font ConfigOption::prevFont() {
    auto it = fontMap.begin();
    for ( it;it != fontMap.end(); ++it) {
        if ((*it).first == fontName) {
            if (it == fontMap.begin()) {
                it = fontMap.end();
            }
            --it;
            break;
        }
    }
    updateFontValue((*it).second,(*it).first);
    return (*it).second;
}


void ConfigOption::updateFont() {
    label.setFont(fontValue);
    value.setFont(fontValue);
    leftButton.second.setFont(fontValue);
    rightButton.second.setFont(fontValue);
}



std::pair<sf::RectangleShape, sf::Text> createButton(const sf::Font& font, const std::string& txt) {
    sf::RectangleShape shape({50, 50});
    shape.setFillColor(sf::Color(169,169,169,40));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2.f);

    sf::Text text(font,txt, 24);
    text.setFillColor(sf::Color::Black);
    return {shape, text};
}


void ConfigOption::setRectColor() {
    button.setFillColor(sf::Color(0,0,0,40));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2);
}

void ConfigOption::changeThemeColor() {
        label.setFillColor(hooverButt);
        value.setFillColor(hooverButt);

        button.setFillColor(colorButt);
        button.setOutlineColor(hooverButt);

        keyDecB.first.setFillColor(colorButt);
        keyDecB.first.setOutlineColor(hooverButt);
        keyDecB.second.setFillColor(hooverButt);
        leftButton.second.setFillColor(hooverButt);
        leftButton.first.setOutlineColor(hooverButt);

        keyIncB.first.setFillColor(colorButt);
        keyIncB.first.setOutlineColor(hooverButt);
        keyIncB.second.setFillColor(hooverButt);
        rightButton.second.setFillColor(hooverButt);
        rightButton.first.setOutlineColor(hooverButt);
}


void ConfigOption::update() {
    updateCSize();
    updateFont();
    changeThemeColor();

    switch (configOptionType) {
        case Lives:
        case WordSize:
        {
            value.setString(std::to_string(intValue));
            break;
        }
        case CSize: {
            value.setString(std::to_string(cSizeVal));
            break;
        }
        case Float: {
            std::ostringstream floatToString;
            floatToString << std::fixed << std::setprecision(1) << floatValue;
            value.setString(floatToString.str());
            break;
        }
        case Bool: {
            value.setString(boolValue ? "ON" : "OFF");
            break;

        }
        case Themes: {
            for (const auto& [name, col] : colorMap) {
                if (name == themeName) {
                    bgColor = col.background;
                    colorButt = col.colorButt;
                    hooverButt = col.hooverButt;
                    value.setString(name);
                    changeThemeColor();
                    return;
                }
            }
           break;
        }
        case FontT: {
            value.setString(fontName);
            break;
        }
    }
}



bool ConfigOption::isIncPressed(const sf::Event::KeyPressed& e) const {
    return e.code == keyInc;
}
bool ConfigOption::isDecPressed(const sf::Event::KeyPressed& e) const {
    return e.code == keyDec;
}


void ConfigOption::draw(sf::RenderWindow& window) const{;
        window.draw(button);
        window.draw(label);
        window.draw(leftButton.first);
        window.draw(leftButton.second);
        window.draw(rightButton.first);
        window.draw(rightButton.second);
        window.draw(keyIncB.first);
        window.draw(keyIncB.second);
        window.draw(keyDecB.first);
        window.draw(keyDecB.second);
        window.draw(value);

}



