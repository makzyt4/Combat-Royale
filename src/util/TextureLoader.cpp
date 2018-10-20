#include "TextureLoader.hpp"


cr::TextureLoader &cr::TextureLoader::getInstance() {
    static cr::TextureLoader instance;

    return instance;
}

sf::Texture* cr::TextureLoader::loadFromFile(const std::string &path) {
    std::string fullPath = "../res/textures/" + path;

    std::map<std::string, sf::Texture*>::iterator it = this->textureMap.find(fullPath);
    sf::Texture* texture = new sf::Texture();

    if (it != this->textureMap.end()) {
        return it->second;
    }
    
    if (!texture->loadFromFile(fullPath.c_str())) {
        return nullptr;
    }

    this->textureMap.insert({fullPath, texture});
    return texture;
}
