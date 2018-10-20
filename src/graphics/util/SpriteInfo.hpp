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
        sf::Sprite* sprite;
        std::string layer;

    public:
        SpriteInfo(const uint8_t &bodyIndex, const std::string &colorType, 
                   const sf::Vector2i &offset, sf::Sprite* sprite,
                   const std::string &layer);

        uint8_t getBodyIndex() const;
        std::string getColorType() const;
        sf::Vector2i getOffset() const;
        sf::Sprite *getSprite() const;
        std::string getLayer() const;

        void setBodyIndex(const uint8_t& bodyIndex);
        void setColorType(const std::string& colorType);
        void setOffset(const sf::Vector2i& offset);
        void setSprite(sf::Sprite* sprite);
        void setLayer(const std::string& layer);

    };

}

#endif
