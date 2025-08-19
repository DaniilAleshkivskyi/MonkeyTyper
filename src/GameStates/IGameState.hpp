#pragma once
#include <SFML/Graphics.hpp>

class IGameState {
public:
    virtual void update(const sf::Event& event) = 0;
    virtual void setDefColor() = 0;
    virtual void draw() = 0;
    virtual void init() = 0;
    virtual ~IGameState() = default;
};
