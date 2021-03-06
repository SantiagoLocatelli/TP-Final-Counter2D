#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <box2d/box2d.h>
#include "Ray.h"

class Hittable{
    protected:
        b2Fixture *fixture;
    
    public:
        virtual void recvDamage(float damage) = 0;
        b2Vec2 getPosition();
        virtual bool isBox() = 0;
};

#endif
