#ifndef CR_RAGDOLL_HPP
#define CR_RAGDOLL_HPP

#include "Entity.hpp"


namespace CR {

    class Ragdoll : public Entity {
    
    private:
        void addLimbs(b2World* world, const b2Vec2 &position);

    public:
        Ragdoll(b2World* world, const b2Vec2 &position);

    };

}

#endif
