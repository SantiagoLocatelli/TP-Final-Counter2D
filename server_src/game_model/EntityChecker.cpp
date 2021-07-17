#include "EntityChecker.h"
#include <algorithm>

EntityChecker::EntityChecker(b2World &world):world(world), hasEntities(false){}

bool EntityChecker::ReportFixture(b2Fixture *fixture){
    hasEntities = true;
    if ((Hittable *)fixture->GetBody()->GetUserData().pointer != nullptr){
        hit.push_back((Hittable*)fixture->GetBody()->GetUserData().pointer);
    }
    return true;
}

bool EntityChecker::areaHasEntities(b2Vec2 p1, b2Vec2 p2){
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(std::min(p1.x,p2.x), std::min(p1.y,p2.y));
    aabb.upperBound = b2Vec2(std::max(p1.x,p2.x), std::max(p1.y,p2.y));

    hasEntities = false;

    world.QueryAABB(this, aabb);
    return hasEntities;
}

std::list<Hittable*> &EntityChecker::getHittableInArea(b2Vec2 p1, b2Vec2 p2){
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(std::min(p1.x,p2.x), std::min(p1.y,p2.y));
    aabb.upperBound = b2Vec2(std::max(p1.x,p2.x), std::max(p1.y,p2.y));

    hit.clear();
    world.QueryAABB(this, aabb);
    return hit;
}
