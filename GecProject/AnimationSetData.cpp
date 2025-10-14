#include "AnimationSetData.h"

AnimationSetData::AnimationSetData(const std::string& textureName, const int& NumOfFrames, const int& xSize, const int& ySize)
{
	m_textureName = textureName;
	m_NumOfFrames = NumOfFrames;
	m_XAndY = sf::Vector2i(xSize, ySize);
}
