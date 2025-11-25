#include "Player.h"
#include "Graphics.h"


Player::Player(const std::string& entName, Graphics* graphics, sf::Vector2f& wandh)
{
	m_health = 100;
	m_pos = { 50,50 };
	m_wandh = wandh;
	m_name = entName;
	m_currentAni = "Idle Ani";
	m_clock.start();
	graphics->CreateSprite(m_name);
	graphics->SetSpritePos(m_name, m_pos);
	graphics->SetSpriteScale(m_name, { 0.2f,0.2f });
	LoadTextures(graphics);
}

void Player::Update(sf::RenderWindow& window, Graphics* graphics)
{
	Inputs(graphics);
	graphics->UpdateSprite(m_name, m_clock, window);
	Draw(graphics, window);
	/*if (m_midJump == false)
		Gravity(graphics);
	else if (m_midJump == true)
		Jump(graphics);*/
}

bool Player::CheckCollision(Entity* other)
{
	return Entity::CheckCollision(other);
}

void Player::Draw(Graphics* graphics, sf::RenderWindow& window)
{
	graphics->DrawSprite(m_name, window);
}

void Player::LoadTextures(Graphics* graphics)
{
	graphics->AddAnimationSet(m_name, "Idle Ani", AnimationSetData("Idle Ani", 15, 432, 521));
	graphics->AddAnimationSet(m_name, "Walk Ani", AnimationSetData("Walk Ani", 10, 432, 521));
	graphics->AddAnimationSet(m_name, "Attack Ani", AnimationSetData("Attack Ani", 8, 432, 521));
	graphics->AddAnimationSet(m_name, "Dead Ani", AnimationSetData("Dead Ani", 12, 632, 528));
}

void Player::Jump(Graphics* graphics)
{
	m_jumpClock.start();
	graphics->MoveSprite(m_name, Direction::Up);
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
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_currentDir = Direction::Up;
		graphics->MoveSprite(m_name, m_currentDir);
		graphics->ChangeTexture(m_name, "Walk Ani");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_currentDir = Direction::Left;
		graphics->MoveSprite(m_name, m_currentDir);
		graphics->ChangeTexture(m_name, "Walk Ani");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_currentDir = Direction::Down;
		graphics->MoveSprite(m_name, m_currentDir);
		graphics->ChangeTexture(m_name, "Walk Ani");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_currentDir = Direction::Right;
		graphics->MoveSprite(m_name, m_currentDir);
		graphics->ChangeTexture(m_name, "Walk Ani");
	}
	
	else
		graphics->ChangeTexture(m_name, "Idle Ani");
	m_currentAni = graphics->GetTexture(m_name);
	m_pos = graphics->GetSpritePos(m_name);
}
