#include "Rectangle.h"
#include <iostream>

void MyRectangle::SetRectangle(const float& left, const float& right, const float& top, const float& bottom)
{
	m_top = top;
	m_bottom = bottom;
	m_left = left;
	m_right = right;
	hitbox.setPosition({ m_left, m_top });
	hitbox.setSize({ m_right - m_left, m_bottom - m_top });
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2);
	hitbox.setFillColor(sf::Color::Transparent);
}

void MyRectangle::Move(const sf::Vector2f& amount)
{
	m_left += amount.x;
	m_right += amount.x;
	m_top += amount.y;
	m_bottom += amount.y;
}

bool MyRectangle::DoTheyIntersect(const MyRectangle& rectangle) const
{
	if (m_left > rectangle.m_right)
		return false;
	if (m_right < rectangle.m_left)
		return false;
	if (m_top > rectangle.m_bottom)
		return false;
	if (m_bottom < rectangle.m_top)
		return false;

	std::cout << "colission" << std::endl;
	return true;
}

