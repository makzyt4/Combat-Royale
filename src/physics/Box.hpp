#ifndef CR_BOX_HPP
#define CR_BOX_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace CR {

    class Box {

    protected:
        b2Body* body;
        b2PolygonShape* shape;

    public:
        Box(b2World *world, const b2Vec2 &position, const b2Vec2 &size, const bool &is_dynamic);

        b2Body* getBody();
        b2PolygonShape* getShape();
        std::vector<b2Vec2> getVertices();
        b2Vec2 getPosition();
        double getAngle();
        
        void drawWireframe(sf::RenderWindow* window, const sf::Color& color);

    };

}

#endif
