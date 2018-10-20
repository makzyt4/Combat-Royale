#ifndef CR_TEXTURELOADER_HPP
#define CR_TEXTURELOADER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace cr {

    class TextureLoader {
    private:
        TextureLoader() = default;

        std::map<std::string, sf::Texture*> textureMap;

    public:

        static TextureLoader &getInstance();

        sf::Texture* loadFromFile(const std::string &path);
    };

}

#endif
