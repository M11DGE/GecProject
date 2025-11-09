#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
    private:
		std::string m_currentAni;
public:
        Enemy(const std::string& entName, Graphics* graphics);
        virtual void Update(sf::RenderWindow& window, Graphics* graphics, sf::Clock& clock, const MyRectangle& rectangle)override;
        virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
		virtual void LoadTextures(Graphics* graphics) override;
};

