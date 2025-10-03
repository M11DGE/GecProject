#pragma once
#include <string>
class AnimationSetData 
{
private:
	std::string m_TextureName;
	int m_NumOfFrames{ 0 };
	int m_SizeX{ 0 };
	int m_Sizey{ 0 };
public:
	AnimationSetData(const std::string name);
};