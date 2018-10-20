#include "PlayerAppearance.hpp"

sf::Color cr::PlayerAppearance::getHairColor() const {
    return this->hairColor;
}

sf::Color cr::PlayerAppearance::getSkinColor() const {
    return this->skinColor;
}

sf::Color cr::PlayerAppearance::getShirtColor() const {
    return this->shirtColor;
}

sf::Color cr::PlayerAppearance::getGlovesColor() const {
    return this->glovesColor;
}

sf::Color cr::PlayerAppearance::getShoesColor() const {
    return this->shoesColor;
}

sf::Color cr::PlayerAppearance::getHatColor() const {
    return this->hatColor;
}

cr::HelmetType cr::PlayerAppearance::getHelmetType() const {
    return this->helmetType;
}

cr::HairType cr::PlayerAppearance::getHairType() const {
    return this->hairType;
}

bool cr::PlayerAppearance::hasSunglasses() const {
    return this->sunglasses;
}

void cr::PlayerAppearance::setHairColor(const sf::Color &hairColor) {
    this->hairColor = hairColor;
}

void cr::PlayerAppearance::setSkinColor(const sf::Color &skinColor) {
    this->skinColor = skinColor;
}

void cr::PlayerAppearance::setShirtColor(const sf::Color &shirtColor) {
    this->shirtColor = shirtColor;
}

void cr::PlayerAppearance::setGlovesColor(const sf::Color &glovesColor) {
    this->glovesColor = glovesColor;
}

void cr::PlayerAppearance::setShoesColor(const sf::Color &shoesColor) {
    this->shoesColor = shoesColor;
}

void cr::PlayerAppearance::setHatColor(const sf::Color &hatColor) {
    this->hatColor = hatColor;
}

void cr::PlayerAppearance::setHelmetType(const cr::HelmetType& helmetType) {
    this->helmetType = helmetType;
}

void cr::PlayerAppearance::setHairType(const cr::HairType& hairType) {
    this->hairType = hairType;
}

void cr::PlayerAppearance::setSunglasses(const bool &sunglasses) {
    this->sunglasses = sunglasses;
}
