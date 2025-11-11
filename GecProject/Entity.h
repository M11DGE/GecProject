#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Rectangle.h"
#include "Direction.h"
#include <iostream>

class Entity
{
private:

protected:
	int m_health;
	std::string m_name;
	sf::Vector2f m_pos;
	sf::Clock m_clock;
	Direction m_currentDir{ Direction::None };

public:
	virtual void Update(sf::RenderWindow& window, Graphics* graphics) = 0;
	virtual void Draw(Graphics* graphics, sf::RenderWindow& window) = 0;
	virtual void LoadTextures(Graphics* graphics) = 0;
	virtual void CheckCollision(Graphics* graphics,const std::string& otherObjectName, const MyRectangle& rect) = 0;
	std::string GetName();
	MyRectangle GetRectangle(Graphics* graphics);
};

