#pragma once
#include <SFML/Graphics.hpp>
#include"AnimationSetData.h"
#include "Rectangle.h"
#include "Direction.h"

class Sprite;
class Graphics
{
private:
	std::unordered_map<std::string, Sprite*> m_spriteMap;
protected:
	std::unordered_map<std::string, sf::Texture*> m_textureMap;
public:
	bool LoadTexture(const std::string& name, const std::string& filename);
	std::string GetTexture(const std::string& name);
	std::string GetSpriteName(const std::string& spriteName);
	bool AddAnimationSet(const std::string& spriteName, const std::string& setName, const AnimationSetData& setData );
	bool CreateSprite(const std::string& name);
	void DrawSprite(const std::string& spriteName, sf::RenderWindow& window);
	void UpdateSprite(const std::string& spriteName, sf::Clock& clock);
	void UpdateSprite(const std::string& spriteName);
	void ChangeTexture(const std::string& spriteName, const std::string& textureName, const bool& midAnimation = false);
	sf::Vector2f GetSpritePos(const std::string& spriteName);
	sf::Vector2f GetSpriteScale(const std::string& spriteName);
	void SetSpritePos(const std::string& spriteName, const sf::Vector2f& distance);
	void SetSpriteScale(const std::string& spriteName, const sf::Vector2f& scale);
	void DrawHealthBar(sf::RenderWindow& window, const sf::Vector2f& position, const float& healthPercent);
};

