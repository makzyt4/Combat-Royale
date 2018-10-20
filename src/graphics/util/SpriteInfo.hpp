#ifndef CR_SPRITEINFO_HPP
#define CR_SPRITEINFO_HPP

#include <inttypes.h>
#include <SFML/Graphics.hpp>

namespace cr {

    class SpriteInfo {

    private:
        uint8_t bodyIndex;
        std::string colorType;
        sf::Vector2i offset;
        std::string layers;
        sf::Sprite* sprite;

    public:
        SpriteInfo(const uint8_t &bodyIndex, 
                   const std::string &colorType, 
                   const sf::Vector2i &offset, 
                   const std::string &layers,
                   sf::Sprite* sprite);

        uint8_t getBodyIndex() const;
        std::string getColorType() const;
        sf::Vector2i getOffset() const;
        std::string getLayers() const;
        sf::Sprite *getSprite() const;

        void setBodyIndex(const uint8_t& bodyIndex);
        void setColorType(const std::string& colorType);
        void setOffset(const sf::Vector2i& offset);
        void setLayers(const std::string& layers);
        void setSprite(sf::Sprite* sprite);

    };

}

#endif
