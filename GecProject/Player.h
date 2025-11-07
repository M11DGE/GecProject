#pragma once
#include "Entity.h"
#include "Rectangle.h"
#include "Direction.h"
#include <iostream>

class Graphics;

class Player :
    public Entity
{
private:
    std::string m_currentAni;
public:
    Player(std::string& entName );
    virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
    virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
    void Inputs(Graphics* graphics);
};

