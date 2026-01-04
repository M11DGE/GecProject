#include "Background.h"

Background::Background(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName, const float& speed, const int& bgnum)
{
	m_name = name;
	m_textureName = texName;
	m_pos = pos;
	m_currentAni = m_textureName;
	m_speed = speed;
	bgNum = bgnum;
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);
	if (bgNum == 2)
		graphics->SetSpriteScale(m_name, { 1,0.75 });
	else if (bgNum == 1)
		graphics->SetSpriteScale(m_name, { 2,1 });
	m_scale = graphics->GetSpriteScale(m_name).y;
	graphics->ChangeTexture(m_name, m_textureName);
	graphics->UpdateSprite(m_name);
}

void Background::LoadTextures(Graphics* graphics)
{
	if (bgNum == 1)
	{
		graphics->AddAnimationSet(m_name, m_textureName, AnimationSetData(m_textureName, 1, 1152, 324));
		m_textures[m_textureName] = AnimationSetData(m_textureName, 1, 1152, 324);
	}
	else if (bgNum == 2)
	{
		graphics->AddAnimationSet(m_name, m_textureName, AnimationSetData(m_textureName, 1, 1209, 401));
		m_textures[m_textureName] = AnimationSetData(m_textureName, 1, 1209, 401);
	}
}

void Background::Update(sf::RenderWindow& window, Graphics* graphics)
{
	UpdateRectangle();
	graphics->UpdateSprite(m_name);
	Draw(graphics, window);
}

void Background::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
	window.draw(m_rectangle.GetHitbox());
}

void Background::Move(Graphics* graphics)
{
	MoveEnt({ -m_speed, 0 }, graphics);
}
