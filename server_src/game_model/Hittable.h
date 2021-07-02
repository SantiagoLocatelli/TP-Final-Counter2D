#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <box2d/box2d.h>
#include "Ray.h"

class Hittable{
    protected:
        b2Fixture *fixture;
    
    public:
        float isHitBy(Ray ray);
        void virtual recvDamage(float damage) = 0;
};

#endif
