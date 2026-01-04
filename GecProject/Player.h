#pragma once
#include "Entity.h"
#include "Rectangle.h"
#include "Direction.h"
#include <iostream>
#include <SFML/Audio.hpp>

class Graphics;

class Player :
    public Entity
{
private:
    sf::Clock m_clock;
	sf::Clock m_coolDownClock;
    int m_roadPos{ 1 };
    bool m_midJump{ false };
    sf::RectangleShape m_healthbar;
public:
    Player(const std::string& entName, Graphics* graphics);
    virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
    virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
    virtual void LoadTextures(Graphics* graphics) override;
    virtual void TakeDamage(const int& damage, Graphics* graphics) override;
    void Inputs(Graphics* graphics);
	int GetHealth() { return m_health; }
    void UpdateRectangle() override;
    void RoadPos();
    void UpdateHealthBar();

};

