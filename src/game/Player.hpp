#ifndef CR_PLAYER_HPP
#define CR_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "../graphics/appearance/PlayerAppearance.hpp"

namespace cr {
    
    class Player {

    private:
        sf::Vector2f position;
        sf::Vector2f velocity;

        PlayerAppearance appearance;

    public:
        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        PlayerAppearance getAppearance();

        void update();
        void draw(sf::RenderWindow* window);
        void control(sf::Event* event);

    };

};

#endif
