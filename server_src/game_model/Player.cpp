#include "Player.h"
#include "Pistol.h"
#include "GodGun.h"
#include "../../common_src/GeneralException.h"
#include <cmath>
#include <iostream>
#include <utility>

Player::Player(World &world, float start_x, float start_y)
:health(100), angle(0), world(world), dead(false)
, weapon(new GodGun(this, &world)){
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(start_x, start_y);
    body = world.b2world.CreateBody(&playerBodyDef);
    body->SetUserData(this);

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

Player::Player(Player&& other): world(other.world){
    this->body = other.body;
    this->body->SetUserData(this);

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

void Player::toggleMovement(Direction dir){
    movement[dir] = !movement[dir];
}
        
void Player::updateVelocity(){
    if (dead)
        GeneralException("Error en Player::updateVelocity: El jugador está muerto\n");
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
    if (dead)
        GeneralException("Error en Player::getPosition: El jugador está muerto\n");

    std::array<float, 2> vec;
    vec[0] = body->GetPosition().x;
    vec[1] = body->GetPosition().y;

    return vec;
}

void Player::recvDamage(float damage){
    health -= damage;
    if (health < 0){
        dead = true;
        world.deleteBody(body);
    }
}

float Player::getHealth() const{
    return health;
}

void Player::setAngle(float angle){
    this->angle = angle;
}

float Player::getAngle() const{
    return angle;
}

void Player::toggleWeapon(){
    if (dead)
        GeneralException("Error en Player::toggleWeapon: El jugador está muerto\n");
    weapon->toggle();
}

bool Player::isDead() const{
    return dead;
}

Player::~Player(){
    if (weapon != nullptr)
        delete weapon;
}

