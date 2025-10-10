#pragma once
#include <string>

struct AnimationSetData 
{
	std::string m_textureName;
	int m_NumOfFrames{ 0 };
	int m_SizeX{ 0 };
	int m_SizeY{ 0 };

	AnimationSetData(const std::string textureName, const int NumOfFrames, const int xSize, const int ySize);
	AnimationSetData() {}
};