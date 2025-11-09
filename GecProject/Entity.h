#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Rectangle.h"
#include "Direction.h"
#include "Rectangle.h"
#include <iostream>

class Entity
{
private:

protected:
	int m_health;
	std::string m_name;
	sf::Vector2f m_pos;
	Direction m_currentDir{ Direction::None };

public:
	virtual void Update(sf::RenderWindow& window, Graphics* graphics, sf::Clock& clock, const MyRectangle& rectangle) = 0;
	virtual void Draw(Graphics* graphics, sf::RenderWindow& window) = 0;
	virtual void LoadTextures(Graphics* graphics) = 0;
	MyRectangle GetRectangle(Graphics* graphics);
};

