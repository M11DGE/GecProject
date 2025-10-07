#include "Sprite.h"

void Sprite::AddAnimationSet(const std::string& name, const AnimationSetData& setData, sf::Texture* texture)
{
	if (m_AnimationSet.find(name) != m_AnimationSet.end())
		return;
	m_AnimationSet[name] = AnimationSet{ setData , texture };
}

void Sprite::DrawSprite(sf::Vector2f, const std::string& spriteAnimationSet, int frameNum, sf::RenderWindow& window, sf::Clock& clock)
{
	sf::Sprite sfmlSprite(*m_AnimationSet[spriteAnimationSet].sfmlTexture);
    int scale = frameNum;


    sfmlSprite.setTextureRect(sf::IntRect({ 0,scale * 521 }, { 432,521 }));
    if (clock.getElapsedTime().asSeconds() >= 0.07f) {
        scale++;
        clock.restart();
        if (scale > 7)
            scale = 0;
    }
    window.draw(sfmlSprite);
}