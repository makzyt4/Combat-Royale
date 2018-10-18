#ifndef CR_ENTITY_HPP
#define CR_ENTITY_HPP

#include <vector>

#include "Box.hpp"

namespace CR {

    class Entity {

    protected:
        std::vector<Box*> boxes;
        std::vector<b2RevoluteJoint*> joints;

    public:
        void addBox(Box* box);
        void addJoint(b2RevoluteJoint* joint);

        std::vector<Box*> getBoxes();
        std::vector<b2RevoluteJoint*> getJoints();

        void drawWireframe(sf::RenderWindow* window, const sf::Color& color);

    };

}

#endif
