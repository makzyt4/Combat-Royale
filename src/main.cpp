#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "./3rdparty/picojson/picojson.h"
#include <chipmunk/chipmunk.h>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2f v(25, 25);

    std::cout << v.x << std::endl;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
