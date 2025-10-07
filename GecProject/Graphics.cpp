#include "Graphics.h"
#include "Sprite.h"

bool Graphics::LoadTexture(const std::string& name, const std::string& filename)
{
    if (m_textureMap.find(name) != m_textureMap.end())
        return true;

    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(filename))
        return false;

    m_textureMap[name] = texture;
    return false;
}
sf::Texture Graphics::GetTexture(const std::string& name)
{
    return *m_textureMap[name];
}

bool Graphics::AddAnimationSet(const std::string& spriteName, const std::string& setName, const AnimationSetData& setData)
{
    if (m_textureMap.find(setData.m_textureName) == m_textureMap.end())
    return false;
    if (m_spriteMap.find(spriteName) == m_spriteMap.end())
        return false;

    m_spriteMap[spriteName]->AddAnimationSet(setName, setData, m_textureMap[setData.m_textureName]);
}

bool Graphics::CreateSprite(const std::string& name)
{
    Sprite* newSprite = new Sprite;
    if (m_spriteMap.find(name) != m_spriteMap.end())
        return false;
    m_spriteMap[name] = newSprite;
    return false;
}
void Graphics::DrawSprite(const std::string& spriteName, sf::Vector2f pos, const std::string& spriteAnimationSet, int frameNum, sf::RenderWindow& window, sf::Clock& clock)
{
    if (m_spriteMap.find(spriteName) == m_spriteMap.end())
        return;
    m_spriteMap[spriteName]->DrawSprite(pos, spriteAnimationSet, 0, window, clock);
}

