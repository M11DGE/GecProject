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
	sf::Vector2f m_wandh;
	Direction m_currentDir{ Direction::None };
	bool m_isColliding{ false };
	MyRectangle m_rectangle;

public:
	Entity() {};
	virtual void Update(sf::RenderWindow& window, Graphics* graphics) = 0;
	virtual void Draw(Graphics* graphics, sf::RenderWindow& window) = 0;
	virtual void LoadTextures(Graphics* graphics) = 0;
	virtual bool CheckCollision(Entity* other) = 0;
	void Gravity(Graphics* graphics);
	std::string GetName();
	MyRectangle GetRectangle(Graphics* graphics);
	void SetColliding(bool colliding) { m_isColliding = colliding; }
	bool IsColliding() const { return m_isColliding; }
	bool CheckCollision(Entity* otherEntity);
	void UpdateRectangle(Graphics* graphics);
};

