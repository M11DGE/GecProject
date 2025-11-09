#include "Entity.h"

MyRectangle Entity::GetRectangle(Graphics* graphics)
{
    return graphics->GetRectangle(m_name);
}
