#pragma once
#include "Entity.h"
class Wall :
    public Entity
{
private:
    std::string m_textureName;
    sf::Clock m_clock;
	sf::RectangleShape m_healthbar;
    sf::RectangleShape m_healthbarback;
public:
    Wall(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName);
    void LoadTextures(Graphics* graphics)override;
    void Update(sf::RenderWindow& window, Graphics* graphics)override;
    void Draw(Graphics* graphics, sf::RenderWindow& window) override;
	void TakeDamage(const int& damage, Graphics* graphics) override;
    void UpdateHealthBar();
};

