#include "Floor.h"

Floor::Floor(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName)
{
	m_name = name;
	m_textureName = texName;
	m_pos = pos;
	m_currentAni = m_textureName;
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);	
	graphics->SetSpriteScale(m_name, { 1,1 });
	m_scale = graphics->GetSpriteScale(m_name).y;
	graphics->ChangeTexture(m_name, m_textureName);
	graphics->UpdateSprite(m_name);
}

void Floor::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, m_textureName, AnimationSetData(m_textureName, 1, 32, 32));
	m_textures[m_textureName] = AnimationSetData(m_textureName, 1, 32, 32);
}

void Floor::Update(sf::RenderWindow& window, Graphics* graphics)
{
	UpdateRectangle();
	Draw(graphics, window);
}

void Floor::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
	window.draw(m_rectangle.GetHitbox());
}