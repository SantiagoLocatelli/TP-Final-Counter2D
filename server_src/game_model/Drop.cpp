#include "Drop.h"

Drop::Drop(World &world, float x, float y, Weapon *weapon):world(world), weapon(weapon){
    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_staticBody;
    boxBodyDef.position.Set(x, y);
    body = world.b2world.CreateBody(&boxBodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.25f;

    fixture = body->CreateFixture(&circleShape, 0);
    fixture->GetUserData().pointer = (uintptr_t)this;
}

Weapon *Drop::getTaken(){
    world.destroyBody(body);
    return weapon;
}

std::array<float, 2> Drop::getPosition(){
    std::array<float, 2> vec;
    vec[0] = body->GetPosition().x;
    vec[1] = body->GetPosition().y;

    return vec;
}

Weapon *Drop::getWeapon(){
    return weapon;
}
