#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "./physics/Box.hpp"
#include "./physics/Entity.hpp"
#include "./physics/Ragdoll.hpp"
#include "../3rdparty/picojson/picojson.h"
#include <sstream>
#include <fstream>


int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    b2World world(b2Vec2(0.0f, 500.0f));

    std::vector<CR::Ragdoll*> ragdolls;

    CR::Box *box2 = new CR::Box(&world, b2Vec2(500.0, 600.0),
                                b2Vec2(50.0, 10.0), false); 

    CR::Entity *entity2 = new CR::Entity();
    entity2->addBox(box2);

    float timeStep = 1.0 / 60.0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    CR::Ragdoll* ragdoll = new CR::Ragdoll(&world, b2Vec2(mousePos.x, mousePos.y));
                    ragdoll->loadFromFile("./resources/json/ragdoll/human_ragdoll.json");
                    ragdolls.push_back(ragdoll); 
                }
            }
        }

        world.Step(timeStep, 8, 3);

        window.clear();
    
        for (CR::Ragdoll* r : ragdolls) {
            r->drawWireframe(&window, sf::Color::Red);
        }

        entity2->drawWireframe(&window, sf::Color::Green);
        window.display();

        sf::sleep(sf::seconds(1.0/60.0));
    }

    return 0;
}
