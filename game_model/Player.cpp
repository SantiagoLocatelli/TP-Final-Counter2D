#include "Player.h"
#include <cmath>

Player::Player(b2World &world, float start_x, float start_y)
:health(100){
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(start_x, start_y);
    body = world.CreateBody(&playerBodyDef);

    b2CircleShape playerShape;
    playerShape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &playerShape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;

    body->CreateFixture(&fixtureDef);
}

Player::Player(Player&& other){
    this->body = other.body;
    this->health = other.health;
    other.body = nullptr;
}

Player& Player::operator=(Player&& other){
    if (this == &other){
        return *this;
    }

    body = other.body;
    health = other.health;

    other.body = nullptr;
}

void Player::applyImpulse(float x, float y){
    //TODO: Ver la mejor forma de mover a los jugadores (velocidad vs impulso vs fuerza)

    body->ApplyLinearImpulseToCenter(b2Vec2(body->GetMass()*x,body->GetMass()*y), true);
}

std::array<float, 2> Player::getPosition(){
    std::array<float, 2> vec;
    vec[0] = body->GetPosition().x;
    vec[1] = body->GetPosition().y;

    return vec;
}

float Player::isHitBy(float x, float y, float angle){
    b2Fixture fixture = *body->GetFixtureList();

    b2RayCastInput input;
    input.p1 = b2Vec2(x,y);
    input.p2 = b2Vec2(x+std::cos(angle) , y+std::sin(angle));
    input.maxFraction = 100; //TODO: Chequear esta constante
    b2RayCastOutput output;
    if (fixture.RayCast(&output, input, 0)){
        return output.fraction;
    }

    return -1;
}

