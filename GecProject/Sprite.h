#pragma once
#include "AnimationSetData.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

 
struct AnimationSet
{
	AnimationSetData setData;
	sf::Texture* sfmlTexture{ nullptr };
	AnimationSet(const AnimationSetData& setDataData, sf::Texture* texture);
	AnimationSet(){}
};

class Sprite
{
private:
	std::unordered_map<std::string, AnimationSet> m_AnimationSet;
	int m_frameNum = 0;
	sf::Sprite* m_sprite;
public:
	Sprite(sf::Texture* texture) { m_sprite = new sf::Sprite(*texture); }
	void AddAnimationSet(const std::string& name,const AnimationSetData& setData, sf::Texture* texture);
	void DrawSprite(sf::Vector2f, const std::string& spriteAnimationSet, sf::RenderWindow& window);
	void Update(sf::Clock& clock);
	void ChangeTexture(const std::string textureName);
};

