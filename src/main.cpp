#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include <vector>
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

    std::vector<b2Vec2> getVertices() {
        int count = this->boxShape->GetVertexCount();
        std::vector<b2Vec2> verts;

        
        for (int i = 0; i < count; i++) {
            b2Vec2 vert = this->boxShape->GetVertex(i);
            verts.push_back(this->box->GetWorldPoint(vert));
        }

        return verts;
    }

    b2Vec2 getPosition() {
        return this->box->GetPosition();
    }

    double getAngle() {
        return this->box->GetAngle();
    }
    
    void drawWireframe(sf::RenderWindow* window) {
        std::vector<b2Vec2> verts = this->getVertices();

        sf::VertexArray lines(sf::LinesStrip, 5);

        for (int i = 0; i < verts.size(); i++) {
            lines[i].position = sf::Vector2f(verts[i].x, verts[i].y);
        }

        lines[4].position = sf::Vector2f(verts[0].x, verts[0].y);

        window->draw(lines);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    b2World world(b2Vec2(0.0f, 1000.0f));
    b2BodyDef groundDef;
    groundDef.position.Set(200.0f, 200.0f);

    Entity *box = new Entity(&world, b2Vec2(50.0, 50.0), b2Vec2(10.0, 10.0), true); 
    Entity *box2 = new Entity(&world, b2Vec2(110.0, 100.0), b2Vec2(50.0, 10.0), false); 
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

        //std::cout << pos.x << ", " << pos.y << std::endl;
        //std::cout << angle << std::endl;

        window.clear();
        box->drawWireframe(&window);
        box2->drawWireframe(&window);
        window.display();

        sf::sleep(sf::seconds(1.0/60.0));
    }

    return 0;
}
