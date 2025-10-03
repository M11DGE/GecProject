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

bool Graphics::AddAnimationSet(const std::string spriteName, const std::string setName, const AnimationSetData& setData)
{
    return false;
}
