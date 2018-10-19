#ifndef CR_RAGDOLL_HPP
#define CR_RAGDOLL_HPP

#include "Entity.hpp"
#include "../util/JsonLoader.hpp"


namespace CR {

    class Ragdoll : public Entity {
    
    private:
        b2World *world;
        b2Vec2 position;

        void addLimbs(b2World *world, const b2Vec2 &position);

    public:
        Ragdoll(b2World *world, const b2Vec2 &position);

        void loadFromFile(const std::string &filename);
    };

}

#endif
