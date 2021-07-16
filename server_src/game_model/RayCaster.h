#ifndef _RAY_CASTER_H_
#define _RAY_CASTER_H_

#include <box2d/box2d.h>
#include "Hittable.h"

class RayCaster: public b2RayCastCallback{
    private:
        b2World &world;
        Hittable *hittable;
        float fraction;

        float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    public:
        explicit RayCaster(b2World &world);
        float castRay(Ray ray, Hittable *&hit);
};

#endif
