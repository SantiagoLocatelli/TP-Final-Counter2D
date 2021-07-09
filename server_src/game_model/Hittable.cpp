#include "Hittable.h"
#include <array>

float Hittable::isHitBy(Ray ray){
    b2RayCastInput input;
    input.p1 = b2Vec2(ray.x,ray.y);
    input.p2 = b2Vec2(ray.x+std::cos(ray.angle) , ray.y+std::sin(ray.angle));
    input.maxFraction = ray.distance;
    b2RayCastOutput output;
    if (fixture->RayCast(&output, input, 0)){
        return output.fraction;
    }

    return -1;
}

b2Vec2 Hittable::getPosition(){
    return fixture->GetBody()->GetPosition();
}

