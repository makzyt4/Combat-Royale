#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "./physics/Box.hpp"
#include "./physics/Entity.hpp"


class Ragdoll : public CR::Entity {
private:
    void addLimbs(b2World* world, const b2Vec2 &position) {
        b2RevoluteJointDef revoluteJointDef;
        revoluteJointDef.collideConnected = false;
        revoluteJointDef.enableLimit = true;

        CR::Box* torso = new CR::Box(world, position + b2Vec2(0, -2), b2Vec2(22, 23), true);
        CR::Box* head = new CR::Box(world, position + b2Vec2(0, -20), b2Vec2(12, 12), true);
        revoluteJointDef.bodyA = torso->getBody();
        revoluteJointDef.bodyB = head->getBody();
        revoluteJointDef.localAnchorA.Set(0, -12);
        revoluteJointDef.localAnchorB.Set(0, 6);
        revoluteJointDef.lowerAngle = -15 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 15 * (M_PI / 180.0);
        b2RevoluteJoint* joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(torso);
        this->addBox(head);
        this->addJoint(joint);

        CR::Box* leftForearm = new CR::Box(world, position + b2Vec2(-20, -9), b2Vec2(13, 7), true);
        revoluteJointDef.bodyB = leftForearm->getBody();
        revoluteJointDef.localAnchorA.Set(-11, -10);
        revoluteJointDef.localAnchorB.Set(5, 0);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftForearm);
        this->addJoint(joint);

        CR::Box* leftUpperLeg = new CR::Box(world, position + b2Vec2(-3, 14), b2Vec2(8, 14), true);
        revoluteJointDef.bodyB = leftUpperLeg->getBody();
        revoluteJointDef.localAnchorA.Set(-3, 9);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftUpperLeg);
        this->addJoint(joint);

        CR::Box* rightForearm = new CR::Box(world, position + b2Vec2(20, -9), b2Vec2(13, 7), true);
        revoluteJointDef.bodyB = rightForearm->getBody();
        revoluteJointDef.localAnchorA.Set(11, -10);
        revoluteJointDef.localAnchorB.Set(-5, 0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightForearm);
        this->addJoint(joint);

        CR::Box* rightUpperLeg = new CR::Box(world, position + b2Vec2(3, 14), b2Vec2(8, 14), true);
        revoluteJointDef.bodyB = rightUpperLeg->getBody();
        revoluteJointDef.localAnchorA.Set(3, 9);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightUpperLeg);
        this->addJoint(joint);

        CR::Box* leftLowerLeg = new CR::Box(world, position + b2Vec2(-3, 30), b2Vec2(8, 14), true);
        revoluteJointDef.bodyA = leftUpperLeg->getBody();
        revoluteJointDef.bodyB = leftLowerLeg->getBody();
        revoluteJointDef.localAnchorA.Set(0, 7);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftLowerLeg);
        this->addJoint(joint);

        CR::Box* rightLowerLeg = new CR::Box(world, position + b2Vec2(3, 30), b2Vec2(8, 14), true);
        revoluteJointDef.bodyA = rightUpperLeg->getBody();
        revoluteJointDef.bodyB = rightLowerLeg->getBody();
        revoluteJointDef.localAnchorA.Set(0, 7);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightLowerLeg);
        this->addJoint(joint);

        CR::Box* leftArm = new CR::Box(world, position + b2Vec2(-23, -9), b2Vec2(20, 7), true);
        revoluteJointDef.bodyA = leftForearm->getBody();
        revoluteJointDef.bodyB = leftArm->getBody();
        revoluteJointDef.localAnchorA.Set(-6, 0);
        revoluteJointDef.localAnchorB.Set(5, 0);
        revoluteJointDef.lowerAngle = 0;
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftArm);
        this->addJoint(joint);

        CR::Box* rightArm = new CR::Box(world, position + b2Vec2(23, -9), b2Vec2(20, 7), true);
        revoluteJointDef.bodyA = rightForearm->getBody();
        revoluteJointDef.bodyB = rightArm->getBody();
        revoluteJointDef.localAnchorA.Set(6, 0);
        revoluteJointDef.localAnchorB.Set(-5, 0);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 0;
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightArm);
        this->addJoint(joint);
    }

public:
    Ragdoll(b2World* world, const b2Vec2 &position) {
        addLimbs(world, position);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    b2World world(b2Vec2(0.0f, 500.0f));

    std::vector<Ragdoll*> ragdolls;

    CR::Box *box2 = new CR::Box(&world, b2Vec2(500.0, 600.0), b2Vec2(50.0, 10.0), false); 

    CR::Entity *entity2 = new CR::Entity();
    entity2->addBox(box2);

    double timeStep = 1.0 / 60.0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    Ragdoll* ragdoll = new Ragdoll(&world, b2Vec2(mousePos.x, mousePos.y));
                    ragdolls.push_back(ragdoll); 
                }
            }
        }

        world.Step(timeStep, 8, 3);

        window.clear();
    
        for (auto r : ragdolls) {
            r->drawWireframe(&window, sf::Color::Red);
        }

        entity2->drawWireframe(&window, sf::Color::Green);
        window.display();

        sf::sleep(sf::seconds(1.0/60.0));
    }

    return 0;
}
