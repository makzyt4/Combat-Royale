#include "Entity.hpp"

void CR::Entity::addBox(CR::Box* box) {
    this->boxes.push_back(box);
}

void CR::Entity::addJoint(b2RevoluteJoint* joint) {
    this->joints.push_back(joint);
}

std::vector<CR::Box*> CR::Entity::getBoxes() {
    return this->boxes;
}

std::vector<b2RevoluteJoint*> CR::Entity::getJoints() {
    return this->joints;
}

void CR::Entity::drawWireframe(sf::RenderWindow* window, const sf::Color& color) {
    for (CR::Box* box : this->boxes) {
        box->drawWireframe(window, color);
    }
}
