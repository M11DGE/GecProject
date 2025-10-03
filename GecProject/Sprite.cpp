#include "Sprite.h"

void Sprite::AddAnimationSet(const std::string& name, const AnimationSetData& setData, sf::Texture* texture)
{
	//check dont already have texture with that name and texture pointer isnt null
	m_AnimationSet[name] = AnimationSet{ setData , texture };
}
