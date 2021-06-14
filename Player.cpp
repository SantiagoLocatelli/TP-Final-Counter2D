#include "Player.h"

Player::Player(b2World &world, float start_x, float start_y){
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(start_x, start_y);
    body = world.CreateBody(&playerBodyDef);

    b2CircleShape playerShape;
    playerShape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &playerShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

void Player::applyImpulse(float x, float y){
    body->ApplyLinearImpulseToCenter(b2Vec2(x,y), true);
}

b2Vec2 Player::getPosition(){
    return body->GetPosition();
}
