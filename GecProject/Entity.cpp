#include "Entity.h"

MyRectangle Entity::GetRectangle()
{
    return m_rectangle;
}

void Entity::Update(sf::RenderWindow& window, Graphics* graphics)
{
	graphics->ChangeTexture(m_name, m_currentAni);
    UpdateRectangle();
    graphics->UpdateSprite(m_name);
    Draw(graphics, window);
}

bool Entity::CheckCollision(Entity* otherEntity, Graphics* graphics)
{
    if (!otherEntity) return false;

    // Skip floor-floor collisions
    if (m_name.find("floor") != std::string::npos && otherEntity->GetName().find("floor") != std::string::npos)
        return false;

    if (m_rectangle.DoTheyIntersect(otherEntity->GetRectangle()))
    {
        switch (m_rectangle.WhichSideCollided(otherEntity->GetRectangle()))
        {
        case Direction::Up:
            m_collisionFlags.top = true;
            break;
        case Direction::Down:
            m_collisionFlags.bottom = true;
            break;
        case Direction::Left:
            m_collisionFlags.left = true;
            break;
        case Direction::Right:
            m_collisionFlags.right = true;
            break;
        }
    }

    return m_rectangle.DoTheyIntersect(otherEntity->GetRectangle());
}

void Entity::UpdateRectangle()
{
    if (m_flip == 1)
	m_rectangle.SetRectangle(m_pos.x,m_pos.x + (m_textures[m_currentAni].x * m_scale) , m_pos.y , m_pos.y + (m_textures[m_currentAni].y * m_scale));
	else if (m_flip == -1)
		m_rectangle.SetRectangle(m_pos.x - (m_textures[m_currentAni].x * m_scale), m_pos.x , m_pos.y , m_pos.y + (m_textures[m_currentAni].y * m_scale));
}

void Entity::MoveEnt(const Direction& direction, Graphics* graphics)
{
    if (m_isColliding)
    {
        if(m_collisionFlags.top == true && direction == Direction::Down)
            m_pos +={ 0,-1.25 };
        if (m_collisionFlags.bottom == true && direction == Direction::Up)
            m_pos +={ 0,1.25 };
        if (m_collisionFlags.left == true && direction == Direction::Right)
            m_pos +={ -1.25,0 };
        if (m_collisionFlags.right == true && direction == Direction::Left)
            m_pos +={ 1.25,0 };
    }
    else if (!m_isColliding)
    {
        switch (m_currentDir)
        {
        case Direction::Up:
            m_pos +={ 0,-0.05 };
            break;
        case Direction::Down:
            m_pos +={ 0,0.05 };
            break;
        case Direction::Left:
            m_pos +={ -0.05,0 };
            Flip(-1, graphics);
            break;
        case Direction::Right:
            m_pos +={ 0.05,0 };
            Flip(1, graphics);
            break;
        }
    }
	graphics->SetSpritePos(m_name, m_pos);
}

void Entity::MoveEnt(const sf::Vector2f& distance, Graphics* graphics)
{
	m_pos += distance;
	graphics->SetSpritePos(m_name, m_pos);
}

void Entity::Flip(const int& flip, Graphics* graphics)
{
	sf::Vector2f scale = graphics->GetSpriteScale(m_name);
    if (m_flip == flip)
        return;
    if (m_flip == 1)
    {
        graphics->SetSpriteScale(m_name, {-(graphics->GetSpriteScale(m_name).x),graphics->GetSpriteScale(m_name).y});
        MoveEnt({(m_textures[m_currentAni].x * graphics->GetSpriteScale(m_name).y), 0 }, graphics);
        m_flip = -1;
        UpdateRectangle();

        return;
    }
    else if (m_flip == -1)
    {
        graphics->SetSpriteScale(m_name, { -(graphics->GetSpriteScale(m_name).x),graphics->GetSpriteScale(m_name).y });
        MoveEnt({-(m_textures[m_currentAni].x * graphics->GetSpriteScale(m_name).y), 0 }, graphics);
        m_flip = 1;
        UpdateRectangle();
        return;
    }
}

void Entity::Gravity(Graphics* graphics)
{
    MoveEnt({ 0,9.81f }, graphics);
}

std::string Entity::GetName()
{
    return m_name;
}

void Entity::ResetCollisionFlags()
{
    m_collisionFlags.Reset();
    m_isColliding = false;
}

bool Entity::IsBlocked(Direction dir) const
{
    switch (dir)
    {
    case Direction::Up:
		return m_collisionFlags.top;
        break;
    case Direction::Down:
		return m_collisionFlags.bottom;
        break;
    case Direction::Left:
		return m_collisionFlags.left;
        break;
    case Direction::Right:
		return m_collisionFlags.right;
        break;
    default:
        return false;
    }
}
