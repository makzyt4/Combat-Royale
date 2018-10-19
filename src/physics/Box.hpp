#ifndef CR_BOX_HPP
#define CR_BOX_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <inttypes.h>


namespace cr {

    class Box {

    protected:
        b2Body* body;
        b2PolygonShape* shape;

    public:
        Box(b2World *world, const b2Vec2 &position, const b2Vec2 &size, const bool &is_dynamic);

        b2Body* getBody() const;
        b2PolygonShape* getShape() const;
        std::vector<b2Vec2> getVertices() const;
        b2Vec2 getPosition() const;
        float getAngle() const ;
        
        void drawWireframe(sf::RenderWindow* window, const sf::Color& color) const;

    };

}

#endif
