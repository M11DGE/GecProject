#pragma once
#include "Entity.h"
#include<iostream>
class Floor :
    public Entity
{
private:
	std::string m_textureName;
public:
    Floor(const std::string& name, const sf::Vector2f& pos, Graphics* graphics, std::string texName);
	void LoadTextures(Graphics* graphics) override;
	virtual void Update(sf::RenderWindow& window, Graphics* graphics) override;
	virtual void Draw(Graphics* graphics, sf::RenderWindow& window) override;
};

