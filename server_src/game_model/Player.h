#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <box2d/box2d.h>
#include <array>
#include <map>
#include "../common/Direction.h"

class Player{
    private:
        float health;
        float angle;
        b2Body *body;
        bool dead;
        std::array<bool, 4> movement;

    public:
        Player(b2World &world, float start_x, float start_y);

        //Métodos de movimiento/posicion
        void toggleMovement(Direction dir);
        void updateVelocity();
        std::array<float, 2> getPosition();
        void setAngle(float angle);
        float getAngle();

        //Métodos de disparos/vida
        void toggleWeapon();
        void recvDamage(float damage);
        float getHealth();
        bool isDead();
        float isHitBy(float x, float y, float angle);

        Player(Player&& other);
        Player& operator=(Player&& other);
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        
};

#endif
