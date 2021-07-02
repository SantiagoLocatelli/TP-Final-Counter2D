#include "Player.h"
#include "Weapon.h"
#include <cmath>
#include <iostream>
#include <utility>

Player::Player(World &world, float start_x, float start_y)
:health(100), angle(0), dead(false), weapon(new Weapon(this, &world)){
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(start_x, start_y);
    body = world.b2world.CreateBody(&playerBodyDef);

    b2CircleShape playerShape;
    playerShape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &playerShape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;

    fixture = body->CreateFixture(&fixtureDef);

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
    other.weapon->changeOwner(this);
    weapon = other.weapon;
    this->fixture = other.fixture;

    other.weapon = nullptr;
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
    other.weapon->changeOwner(this);
    weapon = other.weapon;
    fixture = other.fixture;


    other.weapon = nullptr;
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
        new_imp.y += -1;
    if (movement[DOWN])
        new_imp.y += 1;
    if (movement[LEFT])
        new_imp.x += -1;
    if (movement[RIGHT])
        new_imp.x += 1;

    new_imp.Normalize();
    new_imp *= 6;
    body->SetLinearVelocity(new_imp);
}


std::array<float, 2> Player::getPosition(){
    std::array<float, 2> vec;
    vec[0] = body->GetPosition().x;
    vec[1] = body->GetPosition().y;

    return vec;
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

void Player::setAngle(float angle){
    this->angle = angle;
}

float Player::getAngle(){
    return angle;
}

void Player::toggleWeapon(){
    weapon->toggle();
}

bool Player::isDead(){
    return dead;
}

Player::~Player(){
    if (weapon != nullptr)
        delete weapon;
}

