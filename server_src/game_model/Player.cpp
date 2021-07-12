#include "Player.h"
#include "../../common_src/GeneralException.h"
#include "Pistol.h"
#include "Knife.h"
#include <cmath>
#include <iostream>
#include <utility>

Player::Player(World &world, float start_x, float start_y, GameConfig &config, Team team)
:health(100), angle(0), world(world), dead(false), shooting(false), speed(config.getPlayer().at("speed")), team(team){
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(start_x, start_y);
    body = world.b2world.CreateBody(&playerBodyDef);
    body->GetUserData().pointer = (uintptr_t)this;

    b2CircleShape playerShape;
    playerShape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &playerShape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;

    fixture = body->CreateFixture(&fixtureDef);

    weapons[KNIFE_SLOT] = new Knife(&world, config);
    weapons[KNIFE_SLOT]->changeOwner(this);
    weapons[SECONDARY] = new Pistol(&world, config);
    weapons[SECONDARY]->changeOwner(this);
    weapons[PRIMARY] = nullptr; //TODO: Ojo, peligroso
    weapons[BOMB_SLOT] = nullptr; //TODO: Ojo, peligroso
    currentWeapon = KNIFE_SLOT;
    slotToDestroy = KNIFE_SLOT;

    movement[UP] = false;
    movement[DOWN] = false;
    movement[RIGHT] = false;
    movement[LEFT] = false;
}

Player::Player(Player&& other): world(other.world){
    this->body = other.body;
    this->body->GetUserData().pointer = (uintptr_t)this;

    this->health = other.health;
    this->dead = other.dead;
    this->angle = other.angle;
    this->speed = other.speed;
    this->shooting = other.shooting;
    this->currentWeapon = other.currentWeapon;
    this->slotToDestroy = other.slotToDestroy;
    this->team = other.team;

    this->movement = std::move(other.movement);
    
    for (size_t i = 0; i < other.weapons.size(); i++){
        if (other.weapons[i] != nullptr){
            other.weapons[i]->changeOwner(this);
        }
        this->weapons[i] = other.weapons[i];
        other.weapons[i] = nullptr;
    }

    this->fixture = other.fixture;

    other.body = nullptr;
}

void Player::toggleMovement(Direction dir){
    movement[dir] = !movement[dir];
}
        
void Player::updateVelocity(){
    if (dead)
        GeneralException("Error en Player::updateVelocity: El jugador está muerto\n");
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
    new_imp *= this->speed;
    body->SetLinearVelocity(new_imp);
}


std::array<float, 2> Player::getPosition() const{
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
    
    shooting = !shooting;
    weapons[currentWeapon]->toggle();
}

bool Player::isShooting() const{
    return shooting;
}

WeaponType Player::getWeaponType() const{
    return weapons[currentWeapon]->getType();
}

bool Player::isDead() const{
    return dead;
}

Player::~Player(){
    for(Weapon* w: weapons){
        if (w != nullptr){
            delete w;
        }
    }
}

void Player::dropWeapon(){
    if (currentWeapon != KNIFE_SLOT){ //El cuchillo no se puede tirar
        //TODO: Arreglar los dropeos para que sean consistentes en la distancia
        float x_pos = body->GetPosition().x + std::cos(angle);
        float y_pos = body->GetPosition().y + std::sin(angle);
        new Drop(world, x_pos, y_pos, weapons[currentWeapon]);
        weapons[currentWeapon] = nullptr; //TODO: Esto es peligroso, si el tipo dispara sin arma crashea
        currentWeapon = KNIFE_SLOT;
    }
}

bool Player::canTake(Weapon *weapon){
    if (weapons[weapon->getSlot()] != nullptr)
        return false;
    if (weapon->getType() == BOMB && team == COUNTER)
        return false;

    return true;
}

void Player::takeWeapon(Weapon *weapon){
    if (weapons[weapon->getSlot()] != nullptr){
        delete weapons[weapon->getSlot()];
    }
    weapon->changeOwner(this);
    weapons[weapon->getSlot()] = weapon;
}

void Player::reloadWeapon(){
    weapons[currentWeapon]->reload();
}

void Player::changeWeapon(WeaponSlot slot){
    //Solo cambio de arma si tengo un arma en ese slot
    if (weapons[slot] != nullptr){
        currentWeapon = slot;
    }
}

void Player::destroyWeapon(WeaponSlot slot){
    slotToDestroy = slot;
}


Team Player::getTeam() const{
    return team;
}

void Player::step(float delta){
    if (slotToDestroy != KNIFE_SLOT){
        if (weapons[slotToDestroy] != nullptr){
            delete weapons[slotToDestroy];
            weapons[slotToDestroy] = nullptr;
            if (currentWeapon == slotToDestroy){
                currentWeapon = KNIFE_SLOT;
                slotToDestroy = KNIFE_SLOT;
            }
        }
    }
    for (Weapon* w: weapons){
        if (w != nullptr){
            w->step(delta);
        }
    }
}
