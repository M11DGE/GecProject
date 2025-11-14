#include "Floor.h"

Floor::Floor(const std::string& name, const sf::Vector2f& pos, Graphics* graphics)
{
	m_name = name;
	m_pos = pos;
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	

}

void Floor::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, m_name, AnimationSetData("m_name", 1, 32, 32));
}

void Floor::Update(sf::RenderWindow& window, Graphics* graphics)
{
}

void Floor::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
}
