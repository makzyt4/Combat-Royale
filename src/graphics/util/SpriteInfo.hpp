#ifndef CR_SPRITEINFO_HPP
#define CR_SPRITEINFO_HPP

#include <inttypes.h>
#include <SFML/Graphics.hpp>

namespace cr {

    class SpriteInfo {
    private:
        uint8_t bodyIndex;
        uint8_t colorType;
        sf::Vector2i offset;
        sf::Sprite* sprite;

    public:
        uint8_t getBodyIndex() const;
        uint8_t getColorType() const;
        sf::Vector2i getOffset() const;
        sf::Sprite *getSprite() const;

        void setBodyIndex(const uint8_t& bodyIndex);
        void setColorType(const uint8_t& colorType);
        void setOffset(const sf::Vector2i& offset);
        void setSprite(sf::Sprite* sprite);
    };

}

#endif
