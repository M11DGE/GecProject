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
    sf::Clock m_clock;
	sf::Clock m_jumpClock;
    bool m_midJump{ false };
public:
    Player(const std::string& entName, Graphics* graphics, sf::Vector2f& wandh);
    virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
    virtual bool CheckCollision(Entity* other)override;
    virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
    virtual void LoadTextures(Graphics* graphics) override;
	void Jump(Graphics* graphics);
    void Inputs(Graphics* graphics);
};

