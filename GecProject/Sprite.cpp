#include "Sprite.h"

void Sprite::AddAnimationSet(const std::string& name, const AnimationSetData& setData, sf::Texture* texture)
{
    if (m_AnimationSet.find(name) != m_AnimationSet.end()) {
        std::cout << "not worked" << std::endl;
        return;
    }
    m_AnimationSet[name] = AnimationSet(setData, texture);
    std::cout << "loaded" << name << std::endl;
}

void Sprite::DrawSprite(sf::Vector2f, const std::string& spriteAnimationSet, sf::RenderWindow& window)
{
	    window.draw(*m_sprite);
}

void Sprite::Update(sf::Clock& clock)
{
    m_sprite->setTextureRect(sf::IntRect({ 0,m_frameNum * 521 }, { m_intRectSize }));
    if (clock.getElapsedTime().asSeconds() >= 0.07f) {
        m_frameNum++;
        clock.restart();
        if (m_frameNum > (m_AnimationSet[m_currentTex].setData.m_NumOfFrames - 1))
            m_frameNum = 0;
    }
}

void Sprite::ChangeTexture(const std::string& textureName)
{
    m_sprite->setTexture(*m_AnimationSet[textureName].sfmlTexture);
    m_intRectSize = m_AnimationSet[textureName].setData.m_XAndY;
    m_currentTex = textureName;
}

sf::Vector2f Sprite::GetPos()
{
    return m_sprite->getPosition();
}

void Sprite::SetPos(const sf::Vector2f& amount)
{
    m_sprite->setPosition(m_sprite->getPosition() + amount);
}

void Sprite::Flip(const int& flip)
{
    if (m_flip == flip)
        return;
    if (m_flip == 1)
    {
        m_sprite->setScale({ -1, 1 });
        SetPos({ 421,0 });
        m_flip = -1;
        return;
    }
    else if (m_flip == -1)
    {
        m_sprite->setScale({ 1, 1 });
        SetPos({-421,0});
        m_flip = 1;
        return;
    }
}

AnimationSet::AnimationSet(const AnimationSetData& setDataData, sf::Texture* texture) : setData(setDataData), sfmlTexture(texture)
{
    
}
