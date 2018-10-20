#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "./physics/Entity.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    b2World world(b2Vec2(0.0f, 500.0f));

    std::vector<cr::Entity*> ragdolls;

    cr::Box *box2 = new cr::Box(&world, b2Vec2(500.0, 600.0),
                                b2Vec2(50.0, 10.0), false); 

    cr::Entity *entity2 = new cr::Entity(&world, b2Vec2(50.0, 10.0));
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
                    cr::Entity* ragdoll = new cr::Entity(&world, b2Vec2(mousePos.x, mousePos.y));
                    ragdoll->loadFromJsonFile("../res/json/ragdoll/human_ragdoll.json");
                    ragdolls.push_back(ragdoll); 
                }
            }
        }

        world.Step(timeStep, 8, 3);

        window.clear();
    
        for (cr::Entity* r : ragdolls) {
            r->drawWireframe(&window, sf::Color::Red);
            r->draw(&window);
        }

        entity2->drawWireframe(&window, sf::Color::Green);
        window.display();

        sf::sleep(sf::seconds(1.0/60.0));
    }

    return 0;
}
