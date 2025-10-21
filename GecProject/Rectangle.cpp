#include "Rectangle.h"
#include <iostream>

void MyRectangle::SetRectangle(const float& left, const float& right, const float& top, const float& bottom)
{
	m_top = top;
	m_bottom = bottom;
	m_left = left;
	m_right = right;
}

void MyRectangle::Move(const float& dx, const float& dy)
{
	m_left += dx;
	m_right += dx;
	m_top += dy;
	m_bottom += dy;
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

