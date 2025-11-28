#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Rectangle.h"
#include "Direction.h"
#include "AnimationSetData.h"
#include <iostream>

struct CollisionFlags
{
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;

	void Reset()
	{
		top = bottom = left = right = false;
	}
};

class Entity
{
private:

protected:
	int m_health;
	int m_flip = 1;
	float m_scale = 1.0f;
	std::string m_name;
	sf::Vector2f m_pos;
	sf::Vector2f m_wandh;
	std::string m_currentAni;
	Direction m_currentDir{ Direction::None };
	Direction m_collisionDir{ Direction::None };
	bool m_isColliding{ false };
	MyRectangle m_rectangle;
	CollisionFlags m_collisionFlags;
	std::unordered_map<std::string, sf::Vector2f > m_textures;

public:
	Entity() {};
	virtual void Update(sf::RenderWindow& window, Graphics* graphics);
	virtual void Draw(Graphics* graphics, sf::RenderWindow& window) = 0;

	virtual void LoadTextures(Graphics* graphics) = 0;
	
	void Gravity(Graphics* graphics);

	std::string GetName();
	
	void ResetCollisionFlags();
	bool IsBlocked(Direction dir) const;

	void SetColliding(bool colliding) { m_isColliding = colliding; }
	bool IsColliding() const { return m_isColliding; }
	virtual bool CheckCollision(Entity* otherEntity, Graphics* graphics);

	void UpdateRectangle();
	MyRectangle GetRectangle();

	void MoveEnt(const Direction& direction, Graphics* graphics);
	void MoveEnt(const sf::Vector2f& distance, Graphics* graphics);
	void Flip(const int& flip, Graphics* graphics);
};
