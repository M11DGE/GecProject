#pragma once
#include <SFML/Graphics.hpp>

enum class Side
{
	Top,
	Bottom,
	Left,
	Right,
	None
};

class MyRectangle
{
private:
public:
	float m_top;
	float m_bottom;
	float m_left;
	float m_right;
	sf::RectangleShape hitbox;
	MyRectangle() { m_top = 0, m_bottom = 0, m_left = 0, m_right = 0;  }
	void SetRectangle(const float& left, const float& right, const float& top, const float& bottom);
	void Move(const sf::Vector2f& amount);
	bool DoTheyIntersect(const MyRectangle& rectangle) const ;
	sf::RectangleShape GetHitbox() { return hitbox; }
};

