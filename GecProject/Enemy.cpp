#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(const std::string& entName, Graphics* graphics, const float& startPos)
{
	m_health = 100;
	m_lanePos = (float)(std::rand() % 201);
	m_pos = { 850 + 50 * startPos, 300 + m_lanePos };
	m_name = entName;
	m_gameName = "Zombie";
	m_canCollide = true;
	m_clock.start();
	m_spawnClock.start();
	m_currentAni = "Idle Ani";
	m_currentDir = Direction::Left;
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	graphics->SetSpriteScale(m_name, { 0.2f,0.2f });
	m_scale = graphics->GetSpriteScale(m_name).y;
	LoadTextures(graphics);
	UpdateRectangle();
	graphics->ChangeTexture(m_name, "Idle Ani");
}

void Enemy::Update(sf::RenderWindow& window, Graphics* graphics)
{
	if (m_health <= 0)
	{
		m_currentAni = "Dead Ani";
		graphics->ChangeTexture(m_name, m_currentAni, true);
		UpdateRectangle();
		graphics->UpdateSprite(m_name, m_clock);
		Draw(graphics, window);
		m_destroy = true;
		
	}
	else if (paused)
	{
		m_pauseClock.start();
		m_currentAni = "Idle Ani";
		graphics->ChangeTexture(m_name, m_currentAni);
		graphics->UpdateSprite(m_name, m_clock);
		UpdateRectangle();
		Draw(graphics, window);
		if (m_pauseClock.getElapsedTime().asSeconds() >= 1)
		{
			paused = false;
			m_pauseClock.reset();
		}
	}
	else if (!paused)
	{
		if (!IsColliding())
			Move(graphics);

		graphics->ChangeTexture(m_name, m_currentAni);
		graphics->UpdateSprite(m_name, m_clock);
		UpdateRectangle();
		Draw(graphics, window);
	}
}

bool Enemy::CheckCollision(Entity* other, Graphics* graphics)
{
	if (!paused)
	{
		if (!other) 
			return false;
		if (other->GetName() == m_gameName)
			return false;
		if (m_spawnClock.getElapsedTime().asSeconds() < 0.1f)
			return false;

		if (m_rectangle.DoTheyIntersect(other->GetRectangle()))
		{
		if (other->GetName() == "Wall")
			{
				m_currentAni = "Attack Ani";
				graphics->ChangeTexture(m_name, m_currentAni, true);
				other->TakeDamage(50, graphics);
				paused = true;
				std::cout << "wall" << std::endl;
			}
			else if (other->GetName() == "Player")
			{
				m_currentAni = "Attack Ani";
				graphics->ChangeTexture(m_name, m_currentAni, true);
				other->TakeDamage(10, graphics);
				paused = true;
			}

			else
				m_currentAni = "Walk Ani";

			switch (m_rectangle.WhichSideCollided(other->GetRectangle()))
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
		else
		{
			m_currentAni = "Walk Ani";
			graphics->ChangeTexture(m_name, m_currentAni);
		}
		return m_rectangle.DoTheyIntersect(other->GetRectangle());
	}
	return false;
}

void Enemy::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
}

void Enemy::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "Idle Ani", AnimationSetData("Idle Ani", 15, 432, 521));
	m_textures["Idle Ani"] = AnimationSetData("Idle Ani", 15, 432, 521);
	graphics->AddAnimationSet(m_name, "Walk Ani", AnimationSetData("Walk Ani", 10, 432, 521));
	m_textures["Walk Ani"] = AnimationSetData("Walk Ani", 10, 432, 521);
	graphics->AddAnimationSet(m_name, "Attack Ani", AnimationSetData("Attack Ani", 8, 432, 521));
	m_textures["Attack Ani"] = AnimationSetData("Attack Ani", 8, 432, 521);
	graphics->AddAnimationSet(m_name, "Dead Ani", AnimationSetData("Dead Ani", 12, 632, 528));
	m_textures["Dead Ani"] = AnimationSetData("Dead Ani", 12, 632, 528);
}

void Enemy::Move(Graphics* graphics)
{
	m_currentDir = Direction::Left;
	Flip(-1, graphics);
	m_currentAni = "Walk Ani";
	MoveEnt({-1, 0}, graphics);
}
