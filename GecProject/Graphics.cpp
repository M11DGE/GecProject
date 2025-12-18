#include "Graphics.h"
#include "Sprite.h"

bool Graphics::LoadTexture(const std::string& name, const std::string& filename)
{
    if (m_textureMap.find(name) != m_textureMap.end()) {
        std::cout << "duplicate" << name << std::endl;
        return false;
    }

    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(filename)) {
        std::cout << "cant load" << name << std::endl;
        return false;
    }

    m_textureMap[name] = texture;
    std::cout << "loaded" << name << std::endl;
    return true;
}
std::string Graphics::GetTexture(const std::string& name)
{
    return m_spriteMap[name]->GetCurrentTex();
}

std::string Graphics::GetSpriteName(const std::string& spriteName)
{
    return spriteName;
}

bool Graphics::AddAnimationSet(const std::string& spriteName, const std::string& setName, const AnimationSetData& setData)
{
    if (m_textureMap.find(setData.m_textureName) == m_textureMap.end()) {
        std::cout << "gone wrong" << std::endl;
        return false;
    }
    if (m_spriteMap.find(spriteName) == m_spriteMap.end()) {
        std::cout << "not good"<< std::endl;
        return false;
    }

    m_spriteMap[spriteName]->AddAnimationSet(setName, setData, m_textureMap[setData.m_textureName]);
    std::cout << "alls good" << std::endl;
    return true;
}

bool Graphics::CreateSprite(const std::string& name)
{
    Sprite* newSprite = new Sprite(m_textureMap["Idle Ani"], name);
    if (m_spriteMap.find(name) != m_spriteMap.end())
        return false;
    m_spriteMap[name] = newSprite;
    return false;
}
void Graphics::DrawSprite(const std::string& spriteName, sf::RenderWindow& window)
{
    if (m_spriteMap.find(spriteName) == m_spriteMap.end())
        return;
    m_spriteMap[spriteName]->DrawSprite(window);
}

void Graphics::UpdateSprite(const std::string& spriteName, sf::Clock& clock)
{
    m_spriteMap[spriteName]->Update(clock);
}

void Graphics::UpdateSprite(const std::string& spriteName)
{
    m_spriteMap[spriteName]->Update();
}

void Graphics::ChangeTexture(const std::string& spriteName, const std::string& textureName, const bool& midAnimation)
{
    m_spriteMap[spriteName]->ChangeTexture(textureName, midAnimation);
}

sf::Vector2f Graphics::GetSpritePos(const std::string& spriteName)
{
    return m_spriteMap[spriteName]->GetPos();
}

sf::Vector2f Graphics::GetSpriteScale(const std::string& spriteName)
{
    return m_spriteMap[spriteName]->GetScale();
}

void Graphics::SetSpritePos(const std::string& spriteName, const sf::Vector2f& distance)
{
    m_spriteMap[spriteName]->SetPos(distance);
}

void Graphics::SetSpriteScale(const std::string& spriteName, const sf::Vector2f& scale)
{
	m_spriteMap[spriteName]->SetScale(scale);
}

void Graphics::DrawHealthBar(sf::RenderWindow& window, const sf::Vector2f& position, const float& healthPercent)
{
    sf::RectangleShape backBar(sf::Vector2f(104.0f, 14.0f));
    backBar.setFillColor(sf::Color(50, 50, 50));
    backBar.setPosition(position);
    sf::RectangleShape healthBar(sf::Vector2f(healthPercent * 100.0f, 10.0f));
    healthBar.setFillColor(sf::Color(100, 250, 50));
    healthBar.setPosition({ position.x + 2.0f, position.y + 2.0f });
    window.draw(backBar);
	window.draw(healthBar);
}

int Graphics::GetSpriteFrameNum(const std::string& spriteName)
{
    return m_spriteMap[spriteName]->GetFramNum();
}

