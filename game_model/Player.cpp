#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(b2World &world, float start_x, float start_y)
:health(100), dead(false){
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

    movement[UP] = false;
    movement[DOWN] = false;
    movement[RIGHT] = false;
    movement[LEFT] = false;
}

Player::Player(Player&& other){
    this->body = other.body;
    this->health = other.health;
    this->dead = other.dead;
    this->angle = other.angle;
    this->movement = std::move(other.movement);

    other.body = nullptr;
}

Player& Player::operator=(Player&& other){
    if (this == &other){
        return *this;
    }

    body = other.body;
    health = other.health;
    dead = other.dead;
    angle = other.angle;
    movement = std::move(other.movement);

    other.body = nullptr;

    return *this;
}

void Player::toggleMovement(Direction dir){
    movement[dir] = !movement[dir];
}
        
void Player::updateVelocity(){
    //TODO: Muy hardcodeado, arreglar esto
    b2Vec2 new_imp(0,0);
    if (movement[UP])
        new_imp.x += -1;
    if (movement[DOWN])
        new_imp.x += 1;
    if (movement[LEFT])
        new_imp.y += -1;
    if (movement[RIGHT])
        new_imp.x += 1;

    new_imp.Normalize();
    new_imp *= 50;
    body->ApplyForceToCenter(new_imp, true);
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

void Player::recvDamage(float damage){
    health -= damage;
    if (health < 0){
        dead = true;
    }
}

float Player::getHealth(){
    return health;
}

void Player::rotate(float angle){
    this->angle += angle;
}

float Player::getAngle(){
    return angle;
}

void Player::activateWeapon(){
}

bool Player::isDead(){
    return dead;
}

