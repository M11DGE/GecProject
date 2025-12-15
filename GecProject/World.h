#pragma once
#include "Graphics.h"
#include "Entity.h"
#include "Background.h"
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Direction.h"
#include <vector>
#include "ExternalHeaders.h"

class World
{
private:
	Graphics* m_graphics;
	sf::Clock m_clock;
	std::vector<Entity*> m_entityVec;
	std::vector<Background*> m_backgroundVec;
	int m_fps;

public:
	World() { m_graphics = new Graphics(), m_fps = 0; }
	~World() { delete m_graphics; }
	bool LoadTextures();
	void CreateSprites();
	int Run();
	void update();
	void DefineGUI();
	void UpdateBackgrounds();
};

