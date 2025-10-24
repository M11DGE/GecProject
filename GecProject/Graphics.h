#pragma once
#include <SFML/Graphics.hpp>
#include"AnimationSetData.h"
#include "Rectangle.h"

class Sprite;
class Graphics
{
private:
	std::unordered_map<std::string, Sprite*> m_spriteMap;
protected:
	std::unordered_map<std::string, sf::Texture*> m_textureMap;
public:
	bool LoadTexture(const std::string& name, const std::string& filename);
	sf::Texture GetTexture(const std::string& name);
	bool AddAnimationSet(const std::string& spriteName, const std::string& setName, const AnimationSetData& setData );
	bool CreateSprite(const std::string& name);
	void DrawSprite(const std::string& spriteName, const sf::Vector2f& pos, const std::string& spriteAnimationSet, sf::RenderWindow& window);
	void UpdateSprite(const std::string& spriteName, sf::Clock& clock, const MyRectangle& rect );
	void UpdateSprite(const std::string& spriteName, sf::Clock& clock);
	void MoveSprite(const std::string& spriteName, const sf::Vector2f& distance);
	void ChangeTexture(const std::string& spriteName, const std::string& textureName);
	sf::Vector2f GetSpritePos(const std::string& spriteName);
	void SetSpritePos(const std::string& spriteName, const sf::Vector2f& distance);
	void FlipSprite(const std::string& spriteName, const int& flip);
	MyRectangle GetRectangle(const std::string& spriteName);
};

