#pragma once
#include <string>
#include <SFML/Graphics.hpp>

struct AnimationSetData 
{
	std::string m_textureName;
	int m_NumOfFrames{ 0 };
	sf::Vector2i m_XAndY;

	AnimationSetData(const std::string& textureName, const int& NumOfFrames, const int& xSize, const int& ySize);
	AnimationSetData() {}
};