#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include <vector>
#include <cmath>


class Box {
protected:
    b2Body* body;
    b2PolygonShape* shape;

public:
    Box(b2World *world, const b2Vec2 &position, const b2Vec2 &size, 
        const bool &is_dynamic) { 

        b2BodyDef *boxDef = new b2BodyDef();
        boxDef->position.Set(position.x, position.y);
        boxDef->type = (is_dynamic) ? b2_dynamicBody : b2_staticBody;

        this->body = world->CreateBody(boxDef);

        this->shape = new b2PolygonShape();
        this->shape->SetAsBox(size.x / 2.0f, size.y / 2.0f);

        b2FixtureDef *boxFixDef = new b2FixtureDef();
        boxFixDef->shape = this->shape;
        boxFixDef->density = 1.0f;
        boxFixDef->friction = 0.3f;

        this->body->CreateFixture(boxFixDef);
    }

    b2Body* getBody() {
        return this->body;
    }

    b2PolygonShape* getShape() {
        return this->shape;
    }

    std::vector<b2Vec2> getVertices() {
        int count = this->shape->GetVertexCount();
        std::vector<b2Vec2> verts;

        
        for (int i = 0; i < count; i++) {
            b2Vec2 vert = this->shape->GetVertex(i);
            verts.push_back(this->body->GetWorldPoint(vert));
        }

        return verts;
    }

    b2Vec2 getPosition() {
        return this->body->GetPosition();
    }

    double getAngle() {
        return this->body->GetAngle();
    }
    
    void drawWireframe(sf::RenderWindow* window, const sf::Color& color) {
        std::vector<b2Vec2> verts = this->getVertices();

        sf::VertexArray lines(sf::LinesStrip, 5);

        for (int i = 0; i < verts.size() + 1; i++) {
            lines[i].position = sf::Vector2f(verts[i % verts.size()].x, verts[i % verts.size()].y);
            lines[i].color = color;
        }

        window->draw(lines);
    }
};

class Entity {
protected:
    std::vector<Box*> boxes;
    std::vector<b2RevoluteJoint*> joints;

public:
    void addBox(Box* box) {
        this->boxes.push_back(box);
    }

    void addJoint(b2RevoluteJoint* joint) {
        this->joints.push_back(joint);
    }

    std::vector<Box*> getBoxes() {
        return this->boxes;
    }

    std::vector<b2RevoluteJoint*> getJoints() {
        return this->joints;
    }

    void drawWireframe(sf::RenderWindow* window, const sf::Color& color) {
        for (int i = 0; i < boxes.size(); i++) {
            boxes[i]->drawWireframe(window, color);
        }
    }
};

class Ragdoll : public Entity {
private:
    void addLimbs(b2World* world, const b2Vec2 &position) {
        b2RevoluteJointDef revoluteJointDef;
        revoluteJointDef.collideConnected = false;
        revoluteJointDef.enableLimit = true;

        Box* torso = new Box(world, position + b2Vec2(0, -2), b2Vec2(22, 23), true);
        Box* head = new Box(world, position + b2Vec2(0, -20), b2Vec2(12, 12), true);
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

        Box* leftForearm = new Box(world, position + b2Vec2(-20, -9), b2Vec2(13, 7), true);
        revoluteJointDef.bodyB = leftForearm->getBody();
        revoluteJointDef.localAnchorA.Set(-11, -10);
        revoluteJointDef.localAnchorB.Set(5, 0);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftForearm);
        this->addJoint(joint);

        Box* leftUpperLeg = new Box(world, position + b2Vec2(-3, 14), b2Vec2(8, 14), true);
        revoluteJointDef.bodyB = leftUpperLeg->getBody();
        revoluteJointDef.localAnchorA.Set(-3, 9);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftUpperLeg);
        this->addJoint(joint);

        Box* rightForearm = new Box(world, position + b2Vec2(20, -9), b2Vec2(13, 7), true);
        revoluteJointDef.bodyB = rightForearm->getBody();
        revoluteJointDef.localAnchorA.Set(11, -10);
        revoluteJointDef.localAnchorB.Set(-5, 0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightForearm);
        this->addJoint(joint);

        Box* rightUpperLeg = new Box(world, position + b2Vec2(3, 14), b2Vec2(8, 14), true);
        revoluteJointDef.bodyB = rightUpperLeg->getBody();
        revoluteJointDef.localAnchorA.Set(3, 9);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightUpperLeg);
        this->addJoint(joint);

        Box* leftLowerLeg = new Box(world, position + b2Vec2(-3, 30), b2Vec2(8, 14), true);
        revoluteJointDef.bodyA = leftUpperLeg->getBody();
        revoluteJointDef.bodyB = leftLowerLeg->getBody();
        revoluteJointDef.localAnchorA.Set(0, 7);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftLowerLeg);
        this->addJoint(joint);

        Box* rightLowerLeg = new Box(world, position + b2Vec2(3, 30), b2Vec2(8, 14), true);
        revoluteJointDef.bodyA = rightUpperLeg->getBody();
        revoluteJointDef.bodyB = rightLowerLeg->getBody();
        revoluteJointDef.localAnchorA.Set(0, 7);
        revoluteJointDef.localAnchorB.Set(0, -7);
        revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(rightLowerLeg);
        this->addJoint(joint);

        Box* leftArm = new Box(world, position + b2Vec2(-23, -9), b2Vec2(20, 7), true);
        revoluteJointDef.bodyA = leftForearm->getBody();
        revoluteJointDef.bodyB = leftArm->getBody();
        revoluteJointDef.localAnchorA.Set(-6, 0);
        revoluteJointDef.localAnchorB.Set(5, 0);
        revoluteJointDef.lowerAngle = 0;
        revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
        joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addBox(leftArm);
        this->addJoint(joint);

        Box* rightArm = new Box(world, position + b2Vec2(23, -9), b2Vec2(20, 7), true);
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

    Box *box2 = new Box(&world, b2Vec2(500.0, 600.0), b2Vec2(50.0, 10.0), false); 

    Entity *entity2 = new Entity();
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

        //std::cout << pos.x << ", " << pos.y << std::endl;
        //std::cout << angle << std::endl;

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
