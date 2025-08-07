#include "ConfigOption.hpp"


std::pair<sf::RectangleShape, sf::Text> createButton(const sf::Font& font, const std::string& txt);
std::string ConfigOption::fontName;
sf::Font ConfigOption::fontValue;
sf::Color ConfigOption::colorValue;
float  ConfigOption::floatValue = 0;
float  ConfigOption::minFloatVal = 0;
float  ConfigOption::maxFloatVal = 0;
int ConfigOption::cSizeVal = 30;



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



//BG COLOR/TXT COLOR
ConfigOption::ConfigOption( sf::RectangleShape& button,const sf::Text& label,const sf::Color& newColorValue,const std::map<std::string, sf::Color>& colorMap,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc,ConfigOptionType cOT)
:button(button), label(label),value(fontValue, "", cSizeVal),colorMap(colorMap),keyDec(keyDec),keyDecB(createButton(fontValue, "Decrease\n\t\"" + getDescription(delocalize(keyDec))+ "\"")),keyInc(keyInc),keyIncB(createButton(fontValue, "Increase\n\t\"" + getDescription(delocalize(keyInc))+ "\"")),configOptionType(cOT),leftButton(createButton(fontValue, "<")),rightButton(createButton(fontValue, ">")) {

    if (cOT == TxtColor) {
        colorValue = newColorValue;
    }else if (cOT == BgColor) {
        bgColor = newColorValue;
    }

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


void ConfigOption::updateColorValue(const sf::Color& newValue) {
    if (configOptionType == TxtColor) {
        colorValue = newValue;
    } else if(configOptionType == BgColor) {
        bgColor = newValue;
    }
    update();
}

sf::Color ConfigOption::nextColor() {
    auto it = colorMap.begin();
    sf::Color& current = (configOptionType == TxtColor) ? colorValue : bgColor;
    for ( it;it != colorMap.end(); ++it) {
        if ((*it).second == current) {
            ++it;
            break;
        }
    }
    if (it == colorMap.end()) {
        it = colorMap.begin();
    }
    updateColorValue((*it).second);
    return (*it).second;
}

sf::Color ConfigOption::prevColor() {
    auto it = colorMap.begin();
    sf::Color& current = (configOptionType == TxtColor) ? colorValue : bgColor;
    for ( it;it != colorMap.end(); ++it) {
        if ((*it).second == current) {
            if (it == colorMap.begin()) {
                it = colorMap.end();
            }
            --it;
            break;
        }
    }
    updateColorValue((*it).second);
    return (*it).second;
}


sf::Color ConfigOption::getColorValue() const {
    return (configOptionType == TxtColor) ? colorValue : bgColor;
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


void ConfigOption::update() {
    updateCSize();
    updateFont();
    switch (configOptionType) {
        case Lives:
        case WordSize:
        {
            label.setFillColor(colorValue);
            value.setString(std::to_string(intValue));
            value.setFillColor(colorValue);
            break;
        }
        case CSize: {
            label.setFillColor(colorValue);
            value.setString(std::to_string(cSizeVal));
            value.setFillColor(colorValue);
            break;
        }
        case Float: {
            label.setFillColor(colorValue);
            std::ostringstream floatToString;
            floatToString << std::fixed << std::setprecision(1) << floatValue;
            value.setString(floatToString.str());
            value.setFillColor(colorValue);
            break;
        }
        case Bool: {
            value.setString(boolValue ? "ON" : "OFF");
            label.setFillColor(colorValue);
            value.setFillColor(colorValue);
            break;

        }
        case TxtColor:
        case BgColor : {

            sf::Color activeColor = getColorValue();
            for (const auto& [name, col] : colorMap) {
                if (col == activeColor) {
                    value.setString(name);
                    label.setFillColor(colorValue);
                    value.setFillColor(colorValue);
                    return;
                }
            }
           break;
        }
        case FontT: {

            label.setFillColor(colorValue);
            value.setString(fontName);
            value.setFillColor(colorValue);
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



