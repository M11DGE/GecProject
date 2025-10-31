#include "Player.h"

void Player::Update()
{
	Inputs();
}

void Player::Inputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_pos += {0, -0.05};
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_pos += {-0.05, 0};
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_pos += {0, 0.05};
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_pos += {0.05, 0};
	}
}
