#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <box2d/box2d.h>
#include <array>
#include <map>
#include "../../common_src/Direction.h"
#include "Hittable.h"
#include "Weapon.h"
#include "../../common_src/Utils.h"
#include "GameConfig.h"

class World;
class Weapon;


class Player: public Hittable{
    private:
        float health;
        float angle;
        World &world;
        b2Body *body;
        bool dead;
        bool shooting;
        std::array<bool, 4> movement;
        std::array<Weapon*, 4> weapons;
        WeaponSlot currentWeapon;
        WeaponSlot slotToDestroy;
        float speed;
        Team team;


    public:
        Player(World &world, float start_x, float start_y, GameConfig &config, Team team);

        //Métodos de movimiento/posicion
        void toggleMovement(Direction dir);
        void updateVelocity();
        std::array<float, 2> getPosition() const;
        void setAngle(float angle);
        float getAngle() const;
        Team getTeam() const;

        //Métodos de disparos/vida
        void toggleWeapon();
        void recvDamage(float damage) override;
        float getHealth() const;
        bool isDead() const;
        bool isShooting() const;
        WeaponType getWeaponType() const;
        void reloadWeapon();

        //Inventario
        void dropWeapon();
        bool canTake(Weapon *weapon);
        void takeWeapon(Weapon *weapon);
        void destroyWeapon(WeaponSlot slot);
        void changeWeapon(WeaponSlot slot);
        void step(float delta);

        ~Player();

        Player(Player&& other);
        Player& operator=(Player&& other) = delete;
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

        friend class World;
};

#endif
