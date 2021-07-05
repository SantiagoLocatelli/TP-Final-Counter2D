#include "Box.h"

Box::Box(b2World &world, float x, float y){
    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_staticBody;
    boxBodyDef.position.Set(x, y);
    b2Body* body = world.CreateBody(&boxBodyDef);
    body->GetUserData().pointer = (uintptr_t)this;


    b2PolygonShape boxShape;
    boxShape.SetAsBox(BOX_SIZE/2.0f,BOX_SIZE/2.0f);

    fixture = body->CreateFixture(&boxShape, 0);
}

void Box::recvDamage(float damage){}
