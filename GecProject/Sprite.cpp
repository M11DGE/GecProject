#include "Sprite.h"

void Sprite::AddAnimationSet(const std::string& name, const AnimationSetData& setData, sf::Texture* texture)
{
	if (m_AnimationSet.find(name) != m_AnimationSet.end())
		return;
    m_AnimationSet[name] = AnimationSet(setData, texture);
}

void Sprite::DrawSprite(sf::Vector2f, const std::string& spriteAnimationSet, sf::RenderWindow& window)
{
	    window.draw(*m_sprite);
}

void Sprite::Update(sf::Clock& clock)
{
    m_sprite->setTextureRect(sf::IntRect({ 0,m_frameNum * 521 }, { 432,521 }));
    if (clock.getElapsedTime().asSeconds() >= 0.07f) {
        m_frameNum++;
        clock.restart();
        if (m_frameNum > 7)
            m_frameNum = 0;
    }
}

void Sprite::ChangeTexture(const std::string textureName)
{
    m_sprite->setTexture(*m_AnimationSet[textureName].sfmlTexture);
}

AnimationSet::AnimationSet(const AnimationSetData& setDataData, sf::Texture* texture) : setData(setDataData), sfmlTexture(texture)
{
    
}
