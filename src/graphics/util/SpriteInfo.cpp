#include "SpriteInfo.hpp"

cr::SpriteInfo::SpriteInfo(const uint8_t &bodyIndex, const std::string &colorType, 
           const sf::Vector2i &offset, sf::Sprite* sprite, const std::string &layer) {
    this->bodyIndex = bodyIndex;
    this->colorType = colorType;
    this->offset = offset;
    this->sprite = sprite;
    this->layer = layer;
}

uint8_t cr::SpriteInfo::getBodyIndex() const {
    return this->bodyIndex;
}

std::string cr::SpriteInfo::getColorType() const {
    return this->colorType;
}

sf::Vector2i cr::SpriteInfo::getOffset() const {
    return this->offset;
}

sf::Sprite *cr::SpriteInfo::getSprite() const {
    return this->sprite;
}

std::string cr::SpriteInfo::getLayer() const {
    return this->layer;
}

void cr::SpriteInfo::setBodyIndex(const uint8_t& bodyIndex) {
    this->bodyIndex = bodyIndex;
}

void cr::SpriteInfo::setColorType(const std::string& colorType) {
    this->colorType = colorType;
}

void cr::SpriteInfo::setOffset(const sf::Vector2i& offset) {
    this->offset = offset;
}

void cr::SpriteInfo::setSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}

void cr::SpriteInfo::setLayer(const std::string& layer) {
    this->layer = layer;
}
