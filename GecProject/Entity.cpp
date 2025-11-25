#include "Entity.h"

MyRectangle Entity::GetRectangle(Graphics* graphics)
{
    return graphics->GetRectangle(m_name);
}

bool Entity::CheckCollision(Entity* otherEntity)
{
    if (!otherEntity) return false;

    // Skip floor-floor collisions
    if (m_name.find("floor") != std::string::npos &&
        otherEntity->GetName().find("floor") != std::string::npos)
        return false;

    MyRectangle myRect = GetRectangle(nullptr);  // from Graphics
    MyRectangle otherRect = otherEntity->GetRectangle(nullptr);

    return myRect.DoTheyIntersect(otherRect);
}

void Entity::UpdateRectangle(Graphics* graphics)
{
    if (graphics->IsSpriteFacingRight(m_name))
	m_rectangle.SetRectangle(m_pos.x, m_pos.y, m_pos.x + m_wandh.x, m_pos.y + m_wandh.y);
	else if (!graphics->IsSpriteFacingRight(m_name))
		m_rectangle.SetRectangle(m_pos.x - m_wandh.x, m_pos.y, m_pos.x, m_pos.y + m_wandh.y);
}

void Entity::Gravity(Graphics* graphics)
{
    graphics->MoveSprite(m_name, Direction::Down);
}

std::string Entity::GetName()
{
    return m_name;
}
