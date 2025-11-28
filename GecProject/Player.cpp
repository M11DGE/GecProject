#include "Player.h"
#include "Graphics.h"


Player::Player(const std::string& entName, Graphics* graphics)
{
	m_health = 100;
	m_pos = { 50,50 };
	m_name = entName;
	m_currentAni = "Idle Ani";
	m_clock.start();
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	graphics->SetSpriteScale(m_name, { 0.2f,0.2f });
	m_scale = graphics->GetSpriteScale(m_name).y;
	LoadTextures(graphics);
}

void Player::Update(sf::RenderWindow& window, Graphics* graphics)
{
	Inputs(graphics);
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
	window.draw(m_rectangle.GetHitbox());
}

void Player::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "Idle Ani", AnimationSetData("Idle Ani", 15, 432, 521));
	m_textures["Idle Ani"] = sf::Vector2f(432, 521);
	graphics->AddAnimationSet(m_name, "Walk Ani", AnimationSetData("Walk Ani", 10, 432, 521));
	m_textures["Walk Ani"] = sf::Vector2f(432, 521);
	graphics->AddAnimationSet(m_name, "Attack Ani", AnimationSetData("Attack Ani", 8, 432, 521));
	m_textures["Attack Ani"] = sf::Vector2f(432, 521);
	graphics->AddAnimationSet(m_name, "Dead Ani", AnimationSetData("Dead Ani", 12, 632, 528));
	m_textures["Dead Ani"] = sf::Vector2f(632, 528);
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
		m_midJump = true;
		m_currentAni = "Walk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_currentDir = Direction::Up;
		m_currentAni = "Walk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_currentDir = Direction::Left;
		m_currentAni = "Walk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_currentDir = Direction::Down;
		m_currentAni = "Walk Ani";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_currentDir = Direction::Right;
		m_currentAni = "Walk Ani";
	}
	else
	{
		m_currentDir = Direction::None;
		m_currentAni = "Idle Ani";
	}
	MoveEnt(m_currentDir, graphics);
}
