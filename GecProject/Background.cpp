#include "Background.h"

Background::Background(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName, const float& speed)
{
	m_name = name;
	m_textureName = texName;
	m_pos = pos;
	m_currentAni = m_textureName;
	m_speed = speed;
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);
	graphics->SetSpriteScale(m_name, { 2,1 });
	m_scale = graphics->GetSpriteScale(m_name).y;
	graphics->ChangeTexture(m_name, m_textureName);
	graphics->UpdateSprite(m_name);
}

void Background::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, m_textureName, AnimationSetData(m_textureName, 1, 1152, 324));
	m_textures[m_textureName] = sf::Vector2f(1152, 324);
}

void Background::Update(sf::RenderWindow& window, Graphics* graphics)
{

}

void Background::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
	std::cout << m_name << std::endl;
}

void Background::Move(Graphics* graphics)
{
	MoveEnt({ -m_speed, 0 }, graphics);
}
