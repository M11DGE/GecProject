#pragma once
#include "AnimationSetData.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

 
struct AnimationSet
{
	AnimationSetData setData;
	sf::Texture* sfmlTexture{ nullptr };
};
class Sprite
{
private:
	std::unordered_map<std::string, AnimationSet> m_AnimationSet;
public:
	void AddAnimationSet(const std::string& name,const AnimationSetData& setData, sf::Texture* texture);
	void DrawSprite(sf::Vector2f, const std::string& spriteAnimationSet, int frameNum, sf::RenderWindow& window, sf::Clock& clock);
};

