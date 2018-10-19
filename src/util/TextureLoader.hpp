#ifndef CR_TEXTURELOADER_HPP
#define CR_TEXTURELOADER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace cr {

    class TextureLoader {
    protected:
        static std::map<std::string, sf::Texture*> textureMap;

    public:
        static sf::Texture* getTexture(const std::string &path);
    };

}

std::map<std::string, sf::Texture*> cr::TextureLoader::textureMap;

#endif
