#include "Sprite.h"
#include <cstdlib>

void Sprite::AddAnimationSet(const std::string& name, const AnimationSetData& setData, sf::Texture* texture)
{
    if (m_AnimationSet.find(name) != m_AnimationSet.end()) {
        return;
    }
    m_AnimationSet[name] = AnimationSet(setData, texture);
}

void Sprite::DrawSprite(sf::RenderWindow& window)
{
	    window.draw(*m_sprite);
		window.draw(m_rectangle->GetHitbox());
}

void Sprite::Update(sf::Clock& clock)
{
    m_sprite->setTextureRect(sf::IntRect({ 0,m_frameNum * m_AnimationSet[m_currentTex].setData.m_XAndY.y }, { m_intRectSize }));
        if (clock.getElapsedTime().asSeconds() >= 0.07f) {
            m_frameNum++;
            clock.restart();
            if (m_frameNum > (m_AnimationSet[m_currentTex].setData.m_NumOfFrames - 1))
                m_frameNum = 0;
        }
        if (m_midAnimation == true && m_frameNum == 0)
            m_midAnimation = false;
}

void Sprite::Update()
{
    m_sprite->setTextureRect(sf::IntRect({ 0,m_frameNum * m_AnimationSet[m_currentTex].setData.m_XAndY.y }, { m_intRectSize }));
}

std::string Sprite::GetSpriteName()
{
    return m_name;
}

void Sprite::ChangeTexture(const std::string& textureName, const bool& midAnimation)
{
    if (m_midAnimation == false)
    {
        m_sprite->setTexture(*m_AnimationSet[textureName].sfmlTexture);
        m_intRectSize = m_AnimationSet[textureName].setData.m_XAndY;
        m_currentTex = textureName;
        m_midAnimation = midAnimation;
        if (m_currentTex != textureName)
            m_frameNum = 0;
        return;
    }
    else
    {
        return;
    }
}

sf::Vector2f Sprite::GetPos()
{
    return m_sprite->getPosition();
}

void Sprite::SetPos(const sf::Vector2f& amount)
{
    m_sprite->setPosition(amount);
}

void Sprite::SetScale(const sf::Vector2f& scale)
{
	m_sprite->setScale(scale);
}

sf::Vector2f Sprite::GetScale()
{
    return m_sprite->getScale();
}

AnimationSet::AnimationSet(const AnimationSetData& setDataData, sf::Texture* texture) : setData(setDataData), sfmlTexture(texture)
{
    
}
