#include "PlayerAppearance.hpp"

sf::Color cr::PlayerAppearance::getHairColor() {
    return this->hairColor;
}

sf::Color cr::PlayerAppearance::getSkinColor() {
    return this->skinColor;
}

sf::Color cr::PlayerAppearance::getShirtColor() {
    return this->shirtColor;
}

sf::Color cr::PlayerAppearance::getGlovesColor() {
    return this->glovesColor;
}

sf::Color cr::PlayerAppearance::getShoesColor() {
    return this->shoesColor;
}

sf::Color cr::PlayerAppearance::getHatColor() {
    return this->hatColor;
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
