#include "AssetManager.hpp"

Engine::AssetManager::AssetManager() {

}

Engine::AssetManager::~AssetManager() {

}

void Engine::AssetManager::AddTexture(int id, const std::string &filePath, bool isRepeated/*=false*/)
{
    // Get the reference to a new texture, 
    // if it is correctly loaded then <id> is associated
    // with the unique_ptr pointing to the texture itself
    auto texture = std::make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath))
    {
        texture->setRepeated(isRepeated);
        textures[id] = std::move(texture);
    }
}

void Engine::AssetManager::AddFont(int id, const std::string &filePath)
{
    // Similar to AddTexture
    auto font = std::make_unique<sf::Font>();

    if(font->loadFromFile(filePath))
    {
        fonts[id] = std::move(font);
    }
}

const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(textures.at(id).get());
}

const sf::Font &Engine::AssetManager::GetFont(int id) const
{
    return *(fonts.at(id).get());
}