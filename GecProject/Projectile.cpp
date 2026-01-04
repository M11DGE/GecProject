#include "Projectile.h"

Projectile::Projectile(const std::string& entName, Graphics* graphics, const sf::Vector2f& pos, const Direction& dir)
{
	m_name = entName;
	m_gameName = "Projectile";
	m_winCondition = false;
	m_pos = pos;
	m_speed = 5.f;
	m_currentDir = dir;
	m_clock.start();
    m_collisionClock.start();
	m_canCollide = true;
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);
    if (m_currentDir == Direction::Left)
        Flip(-1, graphics);
	UpdateRectangle();
}

void Projectile::Update(sf::RenderWindow& window, Graphics* graphics)
{
    UpdateRectangle();
    graphics->UpdateSprite(m_name, m_clock);
    MoveEnt(graphics);
	Draw(graphics, window);
}

void Projectile::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
}

void Projectile::LoadTextures(Graphics* graphics)
{
    graphics->AddAnimationSet(m_name, "Projectile Ani", AnimationSetData("Projectile Ani", 1, 27, 27));
    m_textures["Projectile Ani"] = AnimationSetData("Projectile Ani", 1, 27, 27);
	graphics->ChangeTexture(m_name, "Projectile Ani");
    m_currentAni = "Projectile Ani";
}

bool Projectile::CheckCollision(Entity* otherEntity, Graphics* graphics)
{
	if (!otherEntity) return false;
    if (!m_canCollide) return false;

    const float spawnGrace = 0.05f;
    if (m_collisionClock.getElapsedTime().asSeconds() < spawnGrace)
        return false;

    if (m_pos.x > 775.f || m_pos.x < -50.f)
    {
        m_destroy = true;
        return false;
    }

    if (m_rectangle.DoTheyIntersect(otherEntity->GetRectangle()))
    {
        if (otherEntity->GetName() == "Zombie")
            otherEntity->TakeDamage(30, graphics);

        m_destroy = true;
        std::cout << "Projectile hit " << otherEntity->GetName() << std::endl;
        return true;
    }

    return false;
}

void Projectile::MoveEnt(Graphics* graphics)
{
    if (!m_isColliding)
    {
        switch (m_currentDir)
        {
        case Direction::Left:
            m_pos += { -2 * m_speed, 0 };
            Flip(-1, graphics);
            break;
        case Direction::Right:
            m_pos += { 2 * m_speed, 0 };
            Flip(1, graphics);
            break;
        default:
            break;
        }
    }
    graphics->SetSpritePos(m_name, m_pos);

}
