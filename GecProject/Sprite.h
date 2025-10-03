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
};

