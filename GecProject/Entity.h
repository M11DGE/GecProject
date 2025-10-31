#pragma once
#include <SFML/Graphics.hpp>
#include "RedirectCout.h"
#include "Graphics.h"
#include <iostream>

class Entity
{
private:

protected:
	int m_health;
	sf::Vector2f m_pos;

public:
	Entity();
	virtual void Update() = 0;
};

