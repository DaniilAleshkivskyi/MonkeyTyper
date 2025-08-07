#include "PlaceChooseMenu.hpp"
using namespace sf;


namespace ChooseMenu {
    void RectSetVecLeft(std::vector<RectangleShape>& shapes,const RenderWindow& window,float spacing) {
        float totalHeight = 0.f;

        for (const auto& rect : shapes) {
            totalHeight += rect.getSize().y + spacing;
        }

        float startY = (window.getSize().y - totalHeight + spacing) / 2.f;

        for (auto& shape : shapes) {
            float x =  -500 + shape.getSize().x;
            shape.setPosition({ x, startY });
            startY += shape.getSize().y + spacing;
        }
    }

    void updateVecs(std::vector<ConfigOption>& configOptions) {
        for (auto& opt : configOptions) {
            float arrSpace = 10;

            auto mainPosL = opt.value.getGlobalBounds().position.x - arrSpace - opt.leftButton.first.getLocalBounds().size.x;

            auto mainPosR = opt.value.getGlobalBounds().position.x + opt.value.getLocalBounds().size.x + arrSpace ;

            auto yPlace = opt.button.getPosition().y + opt.button.getSize().y / 4.f;


            opt.leftButton.first.setPosition({mainPosL,yPlace});

            opt.rightButton.first.setPosition({mainPosR,yPlace});



            for (auto& btn : { &opt.leftButton, &opt.rightButton }) {
                auto& shape = btn->first;
                auto& text = btn->second;

                auto bounds = text.getLocalBounds();
                text.setOrigin(bounds.position + bounds.size / 2.f);
                text.setPosition(shape.getPosition() + shape.getSize() / 2.f);
            }






            opt.keyDecB.first.setSize({130.f,opt.button.getSize().y});
            opt.keyDecB.first.setPosition({opt.button.getPosition().x + opt.button.getSize().x + 30.f,opt.button.getPosition().y});


            opt.keyIncB.first.setSize({130.f,opt.button.getSize().y});
            opt.keyIncB.first.setPosition({opt.keyDecB.first.getPosition().x + opt.keyDecB.first.getSize().x + 30.f,opt.button.getPosition().y});


            for (auto& btn : {  &opt.keyDecB,&opt.keyIncB }) {
                auto& shape = btn->first;
                auto& text = btn->second;

                auto bounds = text.getLocalBounds();
                text.setOrigin(bounds.position + bounds.size / 2.f);
                text.setPosition(shape.getPosition() + shape.getSize() / 2.f);
            }


        }
    }

    void ConfOptionVecLeft(std::vector<ConfigOption>& configOptions, const RenderWindow& window, float spacing) {
        float totalHeight = 0.f;

        for (const auto& opt : configOptions) {
            totalHeight += opt.button.getSize().y + spacing;
        }


        //start position
        float startY = (window.getSize().y - totalHeight) / 2.f;


        for (auto& opt : configOptions) {
            float x = 50.f;
            opt.button.setPosition({ x, startY });


            auto bounds = opt.label.getLocalBounds();
            opt.label.setOrigin({bounds.position.x , bounds.position.y + bounds.size.y/2});
            opt.label.setPosition({ opt.button.getPosition().x + 10, opt.button.getPosition().y + opt.button.getSize().y/2});
            bounds = opt.value.getLocalBounds();
            opt.value.setOrigin({bounds.position.x + bounds.size.x, bounds.position.y + bounds.size.y / 2});
            opt.value.setPosition({opt.label.getPosition().x + 600.f,opt.button.getPosition().y + opt.button.getSize().y / 2.f});


            startY += opt.button.getSize().y + spacing;


            updateVecs(configOptions);


        }
    }
}