#ifndef _BOX_H_
#define _BOX_H_

#include <box2d/box2d.h>
#include "Hittable.h"

#define BOX_SIZE 1 //en metros

class Box: public Hittable{
    public:
        Box(b2World &world, float x, float y);
        void recvDamage(float damage) override;

        Box(Box&& other);
        Box& operator=(Box&& other) = delete;
        Box(const Box&) = delete;
        Box& operator=(const Box&) = delete;
};

#endif
