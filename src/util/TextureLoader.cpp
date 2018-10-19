#include "TextureLoader.hpp"

sf::Texture* cr::TextureLoader::getTexture(const std::string &path) {
    std::string fullPath = "../res/textures/" + path;
    std::map<std::string, sf::Texture*>::iterator it = textureMap.find(fullPath);
    sf::Texture* texture = new sf::Texture();

    if (it != textureMap.end()) {
        return it->second;
    } else if (!texture->loadFromFile(fullPath.c_str())) {
        return nullptr;
    }

    textureMap.insert({fullPath, texture});
    return texture;
}
