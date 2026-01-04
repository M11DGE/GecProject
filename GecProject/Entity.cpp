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

    if (m_canCollide == true)
    {
        if (m_rectangle.DoTheyIntersect(otherEntity->GetRectangle()))
        {
			MoveEnt(PushEntity(otherEntity->GetRectangle()), graphics);
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
}

sf::Vector2f Entity::PushEntity(const MyRectangle& otherRect)
{
	float pushRight = otherRect.m_right - m_rectangle.m_left;
	float pushLeft = m_rectangle.m_right - otherRect.m_left;
	float pushUp = m_rectangle.m_bottom - otherRect.m_top;
	float pushDown = otherRect.m_bottom - m_rectangle.m_top;

	float minPush = std::min({ pushRight, pushLeft,  pushUp, pushDown });

    if (minPush == pushRight)
    {
        return sf::Vector2f(pushRight+0.5f, 0);
    }
    else if (minPush == pushLeft)
    {
        return sf::Vector2f(-(pushLeft+0.5f), 0);
    }
    else if (minPush == pushUp)
    {
        return sf::Vector2f(0, -(pushUp+0.5f));
    }
    else if (minPush == pushDown)
    {
        return sf::Vector2f(0, pushDown+0.5f);
	}

	return sf::Vector2f(0, 0);
    
}

void Entity::UpdateRectangle()
{
    if (m_flip == 1)
	m_rectangle.SetRectangle(m_pos.x,m_pos.x + (m_textures[m_currentAni].m_XAndY.x * m_scale) , m_pos.y , m_pos.y + (m_textures[m_currentAni].m_XAndY.y * m_scale));
	else if (m_flip == -1)
		m_rectangle.SetRectangle(m_pos.x - (m_textures[m_currentAni].m_XAndY.x * m_scale), m_pos.x , m_pos.y , m_pos.y + (m_textures[m_currentAni].m_XAndY.y * m_scale));
}

void Entity::MoveEnt(Graphics* graphics)
{
    if (m_isColliding)
    {
        if(m_collisionFlags.top == true && m_currentDir == Direction::Down)
            m_pos +={ 0,-1.25 };
        if (m_collisionFlags.bottom == true && m_currentDir == Direction::Up)
            m_pos +={ 0,1.25 };
        if (m_collisionFlags.left == true && m_currentDir == Direction::Right)
            m_pos +={ -1.25,0 };
        if (m_collisionFlags.right == true && m_currentDir == Direction::Left)
            m_pos +={ 1.25,0 };
    }
    else if (!m_isColliding)
    {
        switch (m_currentDir)
        {
        case Direction::Up:
            if (m_pos.y>300)
            m_pos +={ 0,-2 };
            break;
        case Direction::Down:
            if(m_pos.y<550)
            m_pos +={ 0,2 };
            break;
        case Direction::Left:
            m_pos +={ -2,0 };
            Flip(-1, graphics);
            break;
        case Direction::Right:
            if(m_pos.x<770)
            m_pos +={ 2,0 };
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
        MoveEnt({(m_textures[m_currentAni].m_XAndY.x * graphics->GetSpriteScale(m_name).y), 0 }, graphics);
        m_flip = -1;
        UpdateRectangle();

        return;
    }
    else if (m_flip == -1)
    {
        graphics->SetSpriteScale(m_name, { -(graphics->GetSpriteScale(m_name).x),graphics->GetSpriteScale(m_name).y });
        MoveEnt({-(m_textures[m_currentAni].m_XAndY.x * graphics->GetSpriteScale(m_name).y), 0 }, graphics);
        m_flip = 1;
        UpdateRectangle();
        return;
    }
}

void Entity::IsAniFinished(Graphics* graphics)
{
    if (m_midAnimation == true && graphics->GetSpriteFrameNum(m_name) == m_textures[m_currentAni].m_NumOfFrames)
		m_midAnimation = false;
}

void Entity::Gravity(Graphics* graphics)
{
    MoveEnt({ 0,9.81f }, graphics);
}

std::string Entity::GetName()
{
    return m_gameName;
}

sf::Vector2f Entity::GetPos()
{
    return m_pos;
}

sf::Vector2f Entity::GetProjSpawnPoint()
{
    if (m_flip == 1)
        return sf::Vector2f(m_pos.x + (m_textures[m_currentAni].m_XAndY.x * m_scale) + 10, m_pos.y + (m_textures[m_currentAni].m_XAndY.y * m_scale) / 2);
    else
        return sf::Vector2f(m_pos.x - 150, m_pos.y + (m_textures[m_currentAni].m_XAndY.y * m_scale) / 2);
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

void Entity::TakeDamage(const int& damage, Graphics* graphics)
{
    m_health -= damage;
}