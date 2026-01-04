#pragma once
#include "Entity.h"
class Projectile :
    public Entity
{
    private:
    sf::Clock m_clock;
    sf::Clock m_collisionClock;
	float m_speed;
    public:
    Projectile(const std::string& entName, Graphics* graphics, const sf::Vector2f& pos, const Direction& dir);
    virtual void Update(sf::RenderWindow& window, Graphics* graphics)override;
    virtual void Draw(Graphics* graphics, sf::RenderWindow& window)override;
	virtual void LoadTextures(Graphics* graphics) override;
	virtual bool CheckCollision(Entity* otherEntity, Graphics* graphics) override;
    void MoveEnt(Graphics* graphics) override;
};

