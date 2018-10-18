#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include "../3rdparty/picojson/picojson.h"

class Entity {
protected:
    b2BodyDef *boxDef;
    b2PolygonShape *boxShape;
    b2FixtureDef *boxFixDef;

public:
    b2Body *box;

    Entity(b2World *world, const b2Vec2 &position, const b2Vec2 &size, 
           const bool &is_dynamic) { 

        this->boxDef = new b2BodyDef();
        this->boxDef->position.Set(position.x, position.y);
        this->boxDef->type = (is_dynamic) ? b2_dynamicBody : b2_staticBody;

        this->box = world->CreateBody(boxDef);

        this->boxShape = new b2PolygonShape();
        this->boxShape->SetAsBox(size.x, size.y);

        this->boxFixDef = new b2FixtureDef();
        this->boxFixDef->shape = boxShape;
        this->boxFixDef->density = 1.0f;
        this->boxFixDef->friction = 0.3f;

        this->box->CreateFixture(boxFixDef);
    }

    b2Vec2 getPosition() {
        return this->box->GetPosition();
    }

    double getAngle() {
        return this->box->GetAngle();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    b2World world(b2Vec2(0.0f, 10.0f));
    b2BodyDef groundDef;
    groundDef.position.Set(0.0f, 10.0f);

    Entity *box = new Entity(&world, b2Vec2(0.0, 4.0), b2Vec2(1.0, 1.0), true); 
    double timeStep = 1.0 / 60.0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        world.Step(timeStep, 8, 3);

        b2Vec2 pos = box->getPosition();
        double angle = box->getAngle();

        std::cout << pos.x << ", " << pos.y << std::endl;
        std::cout << angle << std::endl;

        window.clear();
        window.draw(shape);
        window.display();

        sf::sleep(sf::seconds(1.0/60.0));
    }

    return 0;
}
