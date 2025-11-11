#include "Entity.h"

MyRectangle Entity::GetRectangle(Graphics* graphics)
{
    return graphics->GetRectangle(m_name);
}

std::string Entity::GetName()
{
    return m_name;
}
