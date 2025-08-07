#include <SFML/Graphics.hpp>



using namespace sf;
//FILE FOR CENTRING DIFFERENT ENTITIES MORE FOR INTERFACE/MENUS


namespace CenterEnt{
    void RectSpTextCentre(Text& text, const RectangleShape& shape, const RenderWindow& window) {
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.position + bounds.size / 2.f);
        text.setPosition(shape.getPosition() + shape.getSize() / 2.f);
    }

    void RectSetCentre(RectangleShape& shape, const RenderWindow& window) {
        shape.setPosition({
            (window.getSize().x - shape.getSize().x) / 2.f,
            (window.getSize().y - shape.getSize().y) / 2.f
        });
    }
}


namespace CenterVecEnt{
    void RectSpTextCentre(std::vector<Text>& texts,
                          std::vector<RectangleShape>& rectVec,
                          const RenderWindow& window) {
        if (texts.size() != rectVec.size()) {
            return; //IF DIFFERENT SIZES WE ARE OUT
        }

        for (auto i = 0; i < texts.size(); ++i) {
            Text& text = texts[i];
            RectangleShape& rect = rectVec[i];

            CenterEnt::RectSpTextCentre(text,rect, window);
        }
    }





    void RectSetVecCentre(std::vector<RectangleShape>& shapes,const RenderWindow& window,float spacing){
        float totalHeight = 0.f;

        for (const auto& rect : shapes) {
            totalHeight += rect.getSize().y + spacing;
        }

        float startY = (window.getSize().y - totalHeight + spacing) / 2.f;

        for (auto& shape : shapes) {
            float x = (window.getSize().x - shape.getSize().x) / 2.f;
            shape.setPosition({ x, startY });
            startY += shape.getSize().y + spacing;
        }
    }
    }








