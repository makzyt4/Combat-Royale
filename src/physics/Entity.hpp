#ifndef CR_ENTITY_HPP
#define CR_ENTITY_HPP

#include <vector>

#include "Box.hpp"
#include "../graphics/util/SpriteInfo.hpp"
#include "../util/JsonLoader.hpp"
#include "../util/TextureLoader.hpp"
#include "../graphics/appearance/PlayerAppearance.hpp"

namespace cr {

    class Entity {

    protected:
        b2World *world;
        b2Vec2 position;

        std::vector<Box*> *boxes;
        std::vector<b2RevoluteJoint*> *joints;
        std::vector<SpriteInfo*> *spriteInfos;

        sf::Texture* texture;

    public:
        Entity(b2World* world, const b2Vec2 &position);

        void addBox(Box* box);
        void addJoint(b2RevoluteJoint* joint);
        void addSpriteInfo(SpriteInfo* spriteInfo);

        std::vector<Box*> *getBoxes() const;
        std::vector<b2RevoluteJoint*> *getJoints() const;
        std::vector<SpriteInfo*> *getSpriteInfos() const;

        void setTexture(sf::Texture* texture);

        void loadFromJsonFile(const std::string &filename);
        void drawWireframe(sf::RenderWindow* window, const sf::Color& color) const;
        void draw(sf::RenderWindow* window) const;
        void draw(sf::RenderWindow* window, PlayerAppearance* appearance) const;
    };

}

#endif
