#include "Enemy.h"

Enemy::Enemy(const std::string& entName, Graphics* graphics)
{
	m_health = 100;
	m_pos = { 200,200 };
	m_name = entName;
	m_currentAni = "Idle Ani";
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);
}

void Enemy::Update(sf::RenderWindow& window, Graphics* graphics, sf::Clock& clock, const MyRectangle& rectangle)
{
	graphics->UpdateSprite(m_name, clock);
	Draw(graphics, window);
}

void Enemy::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, m_pos, m_currentAni, window);
}

void Enemy::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "Idle Ani", AnimationSetData("Idle Ani", 15, 432, 521));
	graphics->AddAnimationSet(m_name, "Walk Ani", AnimationSetData("Walk Ani", 10, 432, 521));
}
