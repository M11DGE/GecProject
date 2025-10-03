#pragma once
#include <SFML/Graphics.hpp>
#include"AnimationSetData.h"

class Sprite;
class Graphics
{
private:
	std::unordered_map<std::string, Sprite*> m_spriteMap;
	std::unordered_map<std::string, sf::Texture*> m_textureMap;
public:
	bool LoadTexture(const std::string& name, const std::string& filename);
	sf::Texture GetTexture(const std::string& name);
	bool AddAnimationSet(const std::string spriteName, const std::string setName, const AnimationSetData& setData );
};

