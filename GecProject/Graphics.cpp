#include "Graphics.h"
#include "Sprite.h"

bool Graphics::LoadTexture(const std::string& name, const std::string& filename)
{
    if (m_textureMap.find(name) != m_textureMap.end())
        return false;

    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(filename))
        return false;

    m_textureMap[name] = texture;
    return true;
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
    return true;
}

bool Graphics::CreateSprite(const std::string& name)
{
    Sprite* newSprite = new Sprite(m_textureMap["Attack Ani"]);
    if (m_spriteMap.find(name) != m_spriteMap.end())
        return false;
    m_spriteMap[name] = newSprite;
    return false;
}
void Graphics::DrawSprite(const std::string& spriteName, sf::Vector2f pos, const std::string& spriteAnimationSet, sf::RenderWindow& window)
{
    if (m_spriteMap.find(spriteName) == m_spriteMap.end())
        return;
    m_spriteMap[spriteName]->DrawSprite(pos, spriteAnimationSet, window);
}

void Graphics::UpdateSprite(const std::string spriteName, sf::Clock& clock)
{
    m_spriteMap[spriteName]->Update(clock);
}

void Graphics::ChangeTexture(const std::string spriteName, const std::string textureName)
{
    m_spriteMap[spriteName]->ChangeTexture(textureName);
}

