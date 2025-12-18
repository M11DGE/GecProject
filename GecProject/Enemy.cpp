#include "Enemy.h"

Enemy::Enemy(const std::string& entName, Graphics* graphics)
{
	m_health = 100;
	m_pos = { 700,200 };
	m_name = entName;
	m_clock.start();
	m_currentAni = "Idle Ani";
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	graphics->SetSpriteScale(m_name, { 0.2f,0.2f });
	m_scale = graphics->GetSpriteScale(m_name).y;
	LoadTextures(graphics);
	graphics->ChangeTexture(m_name, "Idle Ani");
}

void Enemy::Update(sf::RenderWindow& window, Graphics* graphics)
{
	/*Move(graphics);*/
	graphics->ChangeTexture(m_name, m_currentAni);
	graphics->UpdateSprite(m_name, m_clock);
	UpdateRectangle();
	Draw(graphics, window);
}

bool Enemy::CheckCollision(Entity* other, Graphics* graphics)
{
		if (m_rectangle.DoTheyIntersect(other->GetRectangle()) == true && other->GetName() == "Player")
		{
			m_currentAni = "Attack Ani";
			graphics->ChangeTexture(m_name, m_currentAni, true);
			other->TakeDamage(10, graphics);
			std::cout << other->GetName() << std::endl;
		}
	else
		m_currentAni = "Idle Ani";

	if (!other) return false;

	if (m_rectangle.DoTheyIntersect(other->GetRectangle()))
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

	return m_rectangle.DoTheyIntersect(other->GetRectangle());
}

void Enemy::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
	window.draw(m_rectangle.GetHitbox());
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
	MoveEnt({-1.5, 0}, graphics);
}
