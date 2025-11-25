#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
    private:
		std::string m_currentAni;
        sf::Clock m_clock;
public:
        Enemy(const std::string& entName, Graphics* graphics);
        virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
		virtual void CheckCollision(Graphics* graphics, const std::string& otherObjectName, const MyRectangle& rect)override;
        virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
		virtual void LoadTextures(Graphics* graphics) override;
};

