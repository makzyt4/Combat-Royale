#include "Player.hpp"

sf::Vector2f cr::Player::getPosition() {
    return this->position;
}

sf::Vector2f cr::Player::getVelocity() {
    return this->velocity;
}

cr::PlayerAppearance cr::Player::getAppearance() {
    return this->appearance;
}

void cr::Player::update() {
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;

    this->velocity.x *= 0.9;
    this->velocity.y *= 0.9;

    // TODO
}

void cr::Player::draw(sf::RenderWindow* window) {
    // TODO
}

void cr::Player::control(sf::Event* event) {
    // TODO 
}
