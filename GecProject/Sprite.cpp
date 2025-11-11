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

void Sprite::Update(sf::Clock& clock)
{
    m_sprite->setTextureRect(sf::IntRect({ 0,m_frameNum * m_AnimationSet[m_currentTex].setData.m_XAndY.y }, { m_intRectSize }));
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
    int flipOffset = (m_AnimationSet[m_currentTex].setData.m_XAndY.x) * abs(m_sprite->getScale().x);
        sf::Vector2f pos = m_sprite->getPosition();
        float left = pos.x;
        float top = pos.y;
        float width = m_intRectSize.x * abs(m_sprite->getScale().x);
        float height = m_intRectSize.y * m_sprite->getScale().y;
        if (m_sprite->getScale().x > 0)
        m_rectangle->SetRectangle(left, (left + width), top, top + height);
        if (m_sprite->getScale().x < 0)
        m_rectangle->SetRectangle(left - flipOffset, (left + width) - flipOffset, top, (top + height));
}

bool Sprite::Collision(const MyRectangle& rect)
{
    if (m_rectangle->DoTheyIntersect(rect) == true)
    {
        m_collisionDir = m_currentDir;
        return true;
    }
    else
        m_collisionDir = Direction::None;
	return false;
}

std::string Sprite::GetSpriteName()
{
    return m_name;
}

void Sprite::Move(const Direction& dir)
{
    m_currentDir = dir;
    if (m_collisionDir != m_currentDir)
    {
        switch (m_currentDir)
        {
        case Direction::Up:
            m_sprite->move({ 0,-0.05 });
            break;
        case Direction::Down:
            m_sprite->move({ 0,0.05 });
            break;
        case Direction::Left:
            m_sprite->move({ -0.05,0 });
            break;
        case Direction::Right:
            m_sprite->move({ 0.05,0 });
            break;
        }
    }
    else if (m_collisionDir == m_currentDir)
    {
        switch (m_currentDir)
        {
        case Direction::Up:
            m_sprite->move({ 0,0.5 });
            break;
        case Direction::Down:
            m_sprite->move({ 0,-0.5 });
            break;
        case Direction::Left:
            m_sprite->move({ 0.5,0 });
            break;
        case Direction::Right:
            m_sprite->move({ -0.5,0 });
            break;
        }
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
    m_sprite->setPosition(amount);
}

void Sprite::Flip(const int& flip)
{
	float scale = m_sprite->getScale().y;
    if (m_flip == flip)
        return;
    if (m_flip == 1)
    {
        m_sprite->setScale({ -0.2, 0.2 });
        m_sprite->move(sf::Vector2f((m_AnimationSet[m_currentTex].setData.m_XAndY.x) * scale, 0));
        m_flip = -1;
        m_rectangle->Move({ 421, 0 });

        return;
    }
    else if (m_flip == -1)
    {
        m_sprite->setScale({ 0.2, 0.2 });
        m_sprite->move(-(sf::Vector2f((m_AnimationSet[m_currentTex].setData.m_XAndY.x) * scale, 0)));
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
