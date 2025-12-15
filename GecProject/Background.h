#pragma once
#include "Entity.h"
class Background :
    public Entity
{
    public:
    std::string m_textureName;
	sf::Clock m_clock;
    sf::Vector2f m_pos2;
	float m_speed;
    Background(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName, const float& speed);
    void LoadTextures(Graphics* graphics) override;
    void Update(sf::RenderWindow& window, Graphics* graphics) override;
	void Draw(Graphics* graphics, sf::RenderWindow& window) override;
    void Move(Graphics* graphics);
};

