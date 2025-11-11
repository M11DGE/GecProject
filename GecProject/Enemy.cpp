#include "Enemy.h"

Enemy::Enemy(const std::string& entName, Graphics* graphics)
{
	m_health = 100;
	m_pos = { 200,200 };
	m_name = entName;
	m_clock.start();
	m_currentAni = "Idle Ani";
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);
	graphics->ChangeTexture(m_name, "Idle Ani");
}

void Enemy::Update(sf::RenderWindow& window, Graphics* graphics)
{
	graphics->UpdateSprite(m_name, m_clock);
	Draw(graphics, window);
}

void Enemy::CheckCollision(Graphics* graphics, const std::string& otherObjectName, const MyRectangle& rect)
{
	if (otherObjectName != m_name)
	{
		if (graphics->CheckCollision(m_name, rect) == true && otherObjectName == "Player")
		{
			graphics->ChangeTexture(m_name, "Attack Ani");
			std::cout << otherObjectName << std::endl;
		}
	}
	else
		graphics->ChangeTexture(m_name, "Idle Ani");
}

void Enemy::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, m_pos, m_currentAni, window);
}

void Enemy::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "Idle Ani", AnimationSetData("Idle Ani", 15, 432, 521));
	graphics->AddAnimationSet(m_name, "Walk Ani", AnimationSetData("Walk Ani", 10, 432, 521));
	graphics->AddAnimationSet(m_name, "Attack Ani", AnimationSetData("Attack Ani", 8, 432, 521));
	graphics->AddAnimationSet(m_name, "Dead Ani", AnimationSetData("Dead Ani", 12, 632, 528));
}
