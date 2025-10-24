#include "Sprite.h"
#include <cstdlib>

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
		window.draw(m_rectangle->GetHitbox());
}

void Sprite::Update(sf::Clock& clock, const MyRectangle& rect)
{
    m_sprite->setTextureRect(sf::IntRect({ 0,m_frameNum * 521 }, { m_intRectSize }));
    if (clock.getElapsedTime().asSeconds() >= 0.07f) {
        m_frameNum++;
        clock.restart();
        if (m_frameNum > (m_AnimationSet[m_currentTex].setData.m_NumOfFrames - 1))
            m_frameNum = 0;
    }

    UpdateRectangle();
    if (m_rectangle->DoTheyIntersect(rect) == true)
        std::cout << "collision" << std::endl;
    else 
        std::cout << "no collision" << std::endl;
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

    UpdateRectangle();
}

void Sprite::UpdateRectangle()
{
    sf::Vector2f pos = m_sprite->getPosition();
    float left = pos.x;
    float top = pos.y;
    float width = m_intRectSize.x * abs(m_sprite->getScale().x);
    float height = m_intRectSize.y * m_sprite->getScale().y;
    m_rectangle->SetRectangle(left, (left + width), top, top + height);
}

void Sprite::Move(const sf::Vector2f& distance)
{
	m_sprite->move(distance);
	m_rectangle->Move(distance);
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
    m_sprite->setPosition(amount);
}

void Sprite::Flip(const int& flip)
{
    if (m_flip == flip)
        return;
    if (m_flip == 1)
    {
        m_sprite->setScale({ -0.2, 0.2 });
        Move(sf::Vector2f((m_AnimationSet[m_currentTex].setData.m_XAndY.x) * 0.2f, 0));
        m_flip = -1;
        m_rectangle->Move({ 421, 0 });
        return;
    }
    else if (m_flip == -1)
    {
        m_sprite->setScale({ 0.2, 0.2 });
        Move(-(sf::Vector2f((m_AnimationSet[m_currentTex].setData.m_XAndY.x) * 0.2f, 0)));
        m_flip = 1;
        m_rectangle->Move({-421, 0});
        return;
    }
}

MyRectangle Sprite::GetRect()
{
    return *m_rectangle;
}

AnimationSet::AnimationSet(const AnimationSetData& setDataData, sf::Texture* texture) : setData(setDataData), sfmlTexture(texture)
{
    
}
