#include "RayCaster.h"

RayCaster::RayCaster(b2World &world): world(world){}

float RayCaster::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction){
    Hittable *hit = (Hittable *)fixture->GetBody()->GetUserData().pointer;
    if (hit == nullptr)
        return 1;
    
    this->hittable = hit;
    this->fraction = fraction;

    return fraction;
}

float RayCaster::castRay(Ray ray, Hittable *&hit){
    hittable = nullptr;
    b2Vec2 p1(ray.x, ray.y);
    b2Vec2 p2(ray.x+ray.distance*std::cos(ray.angle), ray.y+ray.distance*std::sin(ray.angle));
    world.RayCast(this, p1, p2);

    if (hittable == nullptr)
        return -1;
    
    hit = hittable;
    return ray.distance*fraction;
}