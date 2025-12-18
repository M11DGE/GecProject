#include "Player.h"
#include "Graphics.h"


Player::Player(const std::string& entName, Graphics* graphics)
{
	m_health = 100;
	m_maxHealth = 100;
	m_pos = { 50,500 };
	m_name = entName;
	m_currentAni = "PIdle Ani";
	m_clock.start();
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	graphics->SetSpriteScale(m_name, { 2,2 });
	m_scale = graphics->GetSpriteScale(m_name).y;
	LoadTextures(graphics);
	healthbar.setPosition({ m_pos.x-10, m_pos.y - 20 });
	healthbar.setSize({ 50, 10 });
	healthbar.setFillColor(sf::Color::Red);
}

void Player::Update(sf::RenderWindow& window, Graphics* graphics)
{
	Inputs(graphics);
	RoadPos();
	UpdateHealthBar();
	IsAniFinished(graphics);
	graphics->ChangeTexture(m_name, m_currentAni);
	UpdateRectangle();
	graphics->UpdateSprite(m_name, m_clock);
	Draw(graphics, window);
	/*if (m_midJump == false)
		Gravity(graphics);
	else if (m_midJump == true)
		Jump(graphics);*/
}

void Player::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
	window.draw(healthbar);
	window.draw(m_rectangle.GetHitbox());
}

void Player::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "PIdle Ani", AnimationSetData("PIdle Ani", 4, 50, 50));
	m_textures["PIdle Ani"] = AnimationSetData("PIdle Ani", 4, 30, 50);
	graphics->AddAnimationSet(m_name, "PWalk Ani", AnimationSetData("PWalk Ani", 6, 50, 50));
	m_textures["PWalk Ani"] = AnimationSetData("PWalk Ani", 6, 30, 50);
	graphics->AddAnimationSet(m_name, "PAttack Ani", AnimationSetData("PAttack Ani", 6, 50, 50));
	m_textures["PAttack Ani"] = AnimationSetData("PAttack Ani", 6, 30, 50);
	graphics->AddAnimationSet(m_name, "PDead Ani", AnimationSetData("PDead Ani", 6, 50, 50));
	m_textures["PDead Ani"] = AnimationSetData("PDead Ani", 6, 50, 50);
	graphics->AddAnimationSet(m_name, "PHurt Ani", AnimationSetData("PHurt Ani", 2, 50, 50));
	m_textures["PHurt Ani"] = AnimationSetData("PHurt Ani", 2, 30, 50);
	graphics->AddAnimationSet(m_name, "PAttackRange Ani", AnimationSetData("PAttackRange Ani", 8, 50, 50));
	m_textures["PAttackRange Ani"] = AnimationSetData("PAttackRange Ani", 8, 50, 50);
	std::cout << "done" << std::endl;
}

void Player::TakeDamage(const int& damage, Graphics* graphics)
{
	m_health -= damage;
	m_currentAni = "PHurt Ani";
	graphics->ChangeTexture(m_name, m_currentAni, true);
}

void Player::Jump(Graphics* graphics)
{
	m_jumpClock.start();
	MoveEnt({0,-10}, graphics);
	if (m_jumpClock.getElapsedTime().asSeconds() >= 0.5)
	{
		m_midJump = false;
		m_jumpClock.reset();
	}
}

void Player::Inputs(Graphics* graphics)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		m_currentAni = "PAttack Ani";
		if (m_midAnimation == false)
		graphics->ChangeTexture(m_name, m_currentAni, true);
		UpdateRectangle();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
	{
		m_currentAni = "PAttackRange Ani";
		if (m_midAnimation == false)
		graphics->ChangeTexture(m_name, m_currentAni, true);
		UpdateRectangle();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_currentDir = Direction::Up;
		m_currentAni = "PWalk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_currentDir = Direction::Left;
		m_currentAni = "PWalk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_currentDir = Direction::Down;
		m_currentAni = "PWalk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_currentDir = Direction::Right;
		m_currentAni = "PWalk Ani";
	}
	else
	{
		m_currentDir = Direction::None;
		m_currentAni = "PIdle Ani";
	}
	MoveEnt(m_currentDir, graphics);
}

void Player::UpdateRectangle()
{
	if (m_flip == 1)
		m_rectangle.SetRectangle(m_pos.x, m_pos.x + (m_textures[m_currentAni].m_XAndY.x * m_scale), m_pos.y + 30, m_pos.y + (m_textures[m_currentAni].m_XAndY.y * m_scale));
	else if (m_flip == -1)
		m_rectangle.SetRectangle(m_pos.x - (m_textures[m_currentAni].m_XAndY.x * m_scale), m_pos.x, m_pos.y + 30, m_pos.y + (m_textures[m_currentAni].m_XAndY.y * m_scale));
}

void Player::RoadPos()
{
	if (m_pos.y < 330)
		m_roadPos = 1;
	else if (m_pos.y >= 330 && m_pos.y < 420)
		m_roadPos = 2;
	else if (m_pos.y >= 420)
		m_roadPos = 3;
}

void Player::UpdateHealthBar()
{
	healthbar.setPosition({ m_pos.x - 10, m_pos.y - 20 });
	if (m_health > 0)
		healthbar.setSize({ 50.f * (m_health / m_maxHealth), 10.f });
}
