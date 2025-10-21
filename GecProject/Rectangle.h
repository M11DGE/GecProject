#pragma once
class MyRectangle
{
private:
public:
	float m_top;
	float m_bottom;
	float m_left;
	float m_right;
	MyRectangle() { m_top = 0, m_bottom = 0, m_left = 0, m_right = 0; }
	void SetRectangle(const float& left, const float& right, const float& top, const float& bottom);
	void Move(const float& dx, const float& dy);
	bool DoTheyIntersect(const MyRectangle& rectangle) const ;
};

