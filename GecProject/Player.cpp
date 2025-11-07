#include "Player.h"
#include "Graphics.h"


Player::Player(std::string& entName)
{
	m_health = 100;
	m_pos = { 50,50 };
	m_name = entName;
}

void Player::Update(sf::RenderWindow& window, Graphics* graphics)
{
	Inputs(graphics);
	Draw(graphics, window);
}

void Player::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, m_pos, m_currentAni, window);
}

void Player::Inputs(Graphics* graphics)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_currentDir = Direction::Up;
		graphics->MoveSprite(m_name, m_currentDir);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_currentDir = Direction::Left;
		graphics->MoveSprite(m_name, m_currentDir);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_currentDir = Direction::Down;
		graphics->MoveSprite(m_name, m_currentDir);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_currentDir = Direction::Right;
		graphics->MoveSprite(m_name, m_currentDir);
	}
}
