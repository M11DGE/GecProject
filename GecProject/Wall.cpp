#include "Wall.h"
Wall::Wall(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName)
{
	m_health = 10000;
	m_maxHealth = 10000;
	m_pos = pos;
	m_name = name;
	m_gameName = "Wall";
	m_textureName = texName;
	m_currentAni = m_textureName;
	m_winCondition = true;
	m_clock.start();
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	LoadTextures(graphics);
	m_scale = graphics->GetSpriteScale(m_name).y;
	graphics->ChangeTexture(m_name, m_currentAni);
	graphics->UpdateSprite(m_name);
	m_healthbar.setPosition({ 50, 75 });
	m_healthbar.setSize({ 500, 40 });
	m_healthbar.setFillColor(sf::Color::Red);
	m_healthbarback.setPosition({ 50, 75 });
	m_healthbarback.setSize({ 500, 40 });
	m_healthbarback.setFillColor(sf::Color::Transparent);
	m_healthbarback.setOutlineColor(sf::Color::Black);
	m_healthbarback.setOutlineThickness(2.f);
}

void Wall::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "Barb", AnimationSetData("Barb", 1, 75, 400));
	m_textures["Barb"] = AnimationSetData("Barb", 1, 75, 400);
	graphics->AddAnimationSet(m_name, "DamagedWall", AnimationSetData("DamagedWall", 2, 75, 400));
	m_textures["DamagedWall"] = AnimationSetData("DamagedWall", 2, 75, 400);
}

void Wall::Update(sf::RenderWindow& window, Graphics* graphics)
{
	m_currentAni = "Barb";
	graphics->ChangeTexture(m_name, m_currentAni);
	UpdateRectangle();
	UpdateHealthBar();
	graphics->UpdateSprite(m_name, m_clock);
	Draw(graphics, window);
}

void Wall::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
	window.draw(m_healthbar);
	window.draw(m_healthbarback);
}

void Wall::TakeDamage(const int& damage, Graphics* graphics)
{
	m_health -= damage;
	m_currentAni = "DamagedWall";
	graphics->ChangeTexture(m_name, m_currentAni, true);
	if (m_health <= 0)
	{
		m_destroy = true;
	}
	/*m_currentAni = "Barb";*/

}

void Wall::UpdateHealthBar()
{
	if (m_health > 0)
		m_healthbar.setSize({ (500.f * m_health) / m_maxHealth, 40.f });
}
