#include "SpriteInfo.hpp"

cr::SpriteInfo::SpriteInfo(const uint8_t &bodyIndex, const uint8_t &colorType, 
           const sf::Vector2i &offset, sf::Sprite* sprite) {
    this->bodyIndex = bodyIndex;
    this->colorType = colorType;
    this->offset = offset;
    this->sprite = sprite;
}

uint8_t cr::SpriteInfo::getBodyIndex() const {
    return this->bodyIndex;
}

uint8_t cr::SpriteInfo::getColorType() const {
    return this->colorType;
}

sf::Vector2i cr::SpriteInfo::getOffset() const {
    return this->offset;
}

sf::Sprite *cr::SpriteInfo::getSprite() const {
    return this->sprite;
}

void cr::SpriteInfo::setBodyIndex(const uint8_t& bodyIndex) {
    this->bodyIndex = bodyIndex;
}

void cr::SpriteInfo::setColorType(const uint8_t& colorType) {
    this->colorType = colorType;
}

void cr::SpriteInfo::setOffset(const sf::Vector2i& offset) {
    this->offset = offset;
}

void cr::SpriteInfo::setSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}
