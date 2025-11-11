#pragma once
#include "Entity.h"
#include "Rectangle.h"
#include "Direction.h"
#include "Rectangle.h"
#include <iostream>

class Graphics;

class Player :
    public Entity
{
private:
    std::string m_currentAni;
public:
    Player(const std::string& entName, Graphics* graphics);
    virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
    virtual void CheckCollision(Graphics* graphics,const std::string& otherObjectName, const MyRectangle& rect)override;
    virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
    virtual void LoadTextures(Graphics* graphics) override;
    void Inputs(Graphics* graphics);
};

