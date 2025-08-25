#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../../helpers/Theme.hpp"
#include <iomanip>//for float as float is like 2.0000000000000000 and we wanna do smth like 2.0

enum ConfigOptionType {
    Float,WordSize,Lives,Themes,Bool,FontT,CSize
  };

class ConfigOption {
    public:

    sf::RectangleShape button;
    sf::Text label;
    sf::Text value;


    int intValue = 0;
    int minIntVal = 0;
    int maxIntVal = 0;

    static float floatValue;
    static float minFloatVal;
    static float maxFloatVal;

    bool boolValue = false;

    static std::string themeName;
    static sf::Color bgColor;
    static sf::Color colorButt;
    static sf::Color hooverButt;
    std::map<std::string,Theme> colorMap;

    static int cSizeVal;


    sf::Keyboard::Key keyInc;
    std::pair<sf::RectangleShape, sf::Text> keyIncB;
    sf::Keyboard::Key keyDec;
    std::pair<sf::RectangleShape, sf::Text> keyDecB;


    static sf::Font fontValue;
    static std::string fontName;
    std::map<std::string, sf::Font> fontMap;


    std::pair<sf::RectangleShape, sf::Text> leftButton;
    std::pair<sf::RectangleShape, sf::Text> rightButton;

    ConfigOptionType configOptionType;




    //CONSTRUCTORS

    //INT VALUES
    ConfigOption(sf::RectangleShape& button,const sf::Text& label,int nowIntVal,int minIntVal,int maxIntVal,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc,ConfigOptionType cOT);

    //FLOAT VALUES
    ConfigOption( sf::RectangleShape& button,const sf::Text& label,float floatValue,float minVal,float maxVal,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc);

    //BOOL VALUES
    ConfigOption( sf::RectangleShape& button,const sf::Text& label,const bool& boolValue,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc);

    //THEME
    ConfigOption( sf::RectangleShape& button,const sf::Text& label,const std::map<std::string,Theme>& colorMap,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc,ConfigOptionType cOT);

    //FONT
    ConfigOption( sf::RectangleShape& button,sf::Text& label,const sf::Font& font,const std::map<std::string, sf::Font>& fontMap ,sf::Keyboard::Key keyDec,sf::Keyboard::Key keyInc);



    int updateIntValue(int newValue);
    int getIntValue() const;

    float updateFloatValue(float newValue);
    float getFloatValue() const;


    bool updateBoolValue(const bool& newValue);
    bool getBoolValue() const;


    int updateCSizeValue(int newValue);
    void updateCSize();
    int getCSizeVal();

    Theme nextTheme();
    Theme prevTheme();
    void changeThemeColor();

    void draw(sf::RenderWindow& window) const;


    void updateFont();
    void updateFontValue(const sf::Font& newValue,const std::string& newFontName);
    std::string getFontName() const;
    sf::Font getFont() const;
    sf::Font nextFont();
    sf::Font prevFont();


    void setRectColor();


    bool isIncPressed(const sf::Event::KeyPressed& e) const;
    bool isDecPressed(const sf::Event::KeyPressed& e) const;


    void update();
};


