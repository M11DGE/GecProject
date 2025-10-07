#include "AnimationSetData.h"

AnimationSetData::AnimationSetData(const std::string textureName, const int NumOfFrames, const int xSize, const int ySize)
{
	m_textureName = textureName;
	m_NumOfFrames = NumOfFrames;
	m_SizeX = xSize;
	m_SizeY = ySize;
}
