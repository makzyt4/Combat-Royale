#include "SpriteInfo.hpp"

cr::SpriteInfo::SpriteInfo(const uint8_t &bodyIndex, 
                           const std::string &colorType, 
                           const sf::Vector2i &offset,
                           const std::vector<std::string> &layers,
                           sf::Sprite* sprite) {
    this->bodyIndex = bodyIndex;
    this->colorType = colorType;
    this->offset = offset;
    this->layers = layers;
    this->sprite = sprite;
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

std::vector<std::string> cr::SpriteInfo::getLayers() const {
    return this->layers;
}

sf::Sprite *cr::SpriteInfo::getSprite() const {
    return this->sprite;
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

void cr::SpriteInfo::setLayers(const std::vector<std::string>& layer) {
    this->layers = layers;
}

void cr::SpriteInfo::setSprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}
