#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
    private:
        sf::Clock m_clock;
public:
        Enemy(const std::string& entName, Graphics* graphics);
        virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
		virtual bool CheckCollision(Entity* other, Graphics* graphics)override;
        virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
		virtual void LoadTextures(Graphics* graphics) override;
        void Move(Graphics* graphics);
};

