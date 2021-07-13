#ifndef _COLLISION_HANDLER_H_
#define _COLLISION_HANDLER_H_

#include <box2d/box2d.h>

class CollisionHandler : public b2ContactListener{
    public:
        void BeginContact(b2Contact* contact) override;      
};

#endif
