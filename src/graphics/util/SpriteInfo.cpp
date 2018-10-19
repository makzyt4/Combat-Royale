#include "SpriteInfo.hpp"

uint8_t getBodyIndex() const {
    return this->bodyIndex;
}

uint8_t getColorType() const {
    return this->colorType;
}

sf::Vector2i getOffset() const {
    return this->offset;
}

sf::Sprite *getSprite() const {
    return this->sprite;
}

void setBodyIndex(const uint8_t& bodyIndex) {
    this->bodyIndex = bodyIndex;
}

void setColorType(const uint8_t& colorType) {
    this->colorType = colorType;
}

void setOffset(const sf::Vector2i& offset) {
    this->offset = offset;
}

void setSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}
