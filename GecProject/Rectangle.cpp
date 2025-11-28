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
	return true;
}

Direction MyRectangle::WhichSideCollided(const MyRectangle& rectangle) const
{
	if (m_left > rectangle.m_right) return Direction::None;
	if (m_right < rectangle.m_left) return Direction::None;
	if (m_top > rectangle.m_bottom) return Direction::None;
	if (m_bottom < rectangle.m_top) return Direction::None;

	// Compute overlap distances
	float overlapLeft = m_right - rectangle.m_left;
	float overlapRight = rectangle.m_right - m_left;
	float overlapTop = m_bottom - rectangle.m_top;
	float overlapBottom = rectangle.m_bottom - m_top;

	// Find smallest overlap
	float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

	if (minOverlap == overlapLeft)
		return Direction::Left;
	if (minOverlap == overlapRight)
		return Direction::Right;
	if (minOverlap == overlapTop)
		return Direction::Up;
	if (minOverlap == overlapBottom)
		return Direction::Down;

	return Direction::None;
}

