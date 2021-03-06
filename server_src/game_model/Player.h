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
        World &world;
        b2Body *body;
        GameConfig &config;
        std::array<bool, 4> movement;

        std::array<Weapon*, 4> weapons;
        WeaponSlot currentWeapon;
        WeaponSlot slotToDestroy;

        bool dead;
        float health;
        float angle;
        Team team;
        bool defusing;
        float defuseTime;
        int money;

        void setBody(float x, float y);

    public:
        bool canMove;
        bool shot;
        
        Player(World &world, float start_x, float start_y, GameConfig &config, Team team);

        void reset(float x, float y, Team team);
        void step(float delta);

        void toggleMovement(Direction dir);
        void updateVelocity();
        std::array<float, 2> getPosition() const;
        void setAngle(float angle);
        float getAngle() const;
        Team getTeam() const;
        int getMoney() const;
        void addMoney(int money);

        void toggleWeapon();
        void recvDamage(float damage) override;
        float getHealth() const;
        bool isDead() const;
        std::array<WeaponType, 4> getWeapons() const;
        WeaponSlot getWeaponSlot() const;
        void reloadWeapon();

        void dropWeapon();
        bool canTake(Weapon *weapon);
        void takeWeapon(Weapon *weapon);
        void destroyWeapon(WeaponSlot slot);
        void changeWeapon(WeaponSlot slot);
        void toggleDefuse();
        int getAmmo() const;
        void buyWeapon(WeaponType weaponType);
        bool isBox() override;

        ~Player();

        Player(Player&& other);
        Player& operator=(Player&& other) = delete;
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

        friend class World;
};

#endif
