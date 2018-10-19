#ifndef CR_ENTITY_HPP
#define CR_ENTITY_HPP

#include <vector>

#include "Box.hpp"
#include "../util/JsonLoader.hpp"

namespace cr {

    class Entity {

    protected:
        b2World *world;
        b2Vec2 position;

        std::vector<Box*> *boxes;
        std::vector<b2RevoluteJoint*> *joints;
        std::vector<sf::Sprite*> *sprites;

        sf::Texture* texture;

    public:
        Entity(b2World* world, const b2Vec2 &position);

        void addBox(Box* box);
        void addJoint(b2RevoluteJoint* joint);
        void addSprite(sf::Sprite* sprite);

        std::vector<Box*> *getBoxes() const;
        std::vector<b2RevoluteJoint*> *getJoints() const;
        std::vector<sf::Sprite*> *getSprites() const;

        void setTexture(sf::Texture* texture);

        void loadFromJsonFile(const std::string &filename);
        void drawWireframe(sf::RenderWindow* window, const sf::Color& color) const;
        void draw(sf::RenderWindow* window);

    };

}

#endif
