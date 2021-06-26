#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <box2d/box2d.h>
#include <array>
#include <map>
#include "Weapon.h"

enum Direction {UP, DOWN, LEFT, RIGHT};

class Player{
    private:
        float health;
        float angle;
        b2Body *body;
        bool dead;
        Weapon weapon;
        std::map<Direction, bool> movement;

    public:
        Player(b2World &world, float start_x, float start_y);

        //Métodos de movimiento/posicion
        void toggleMovement(Direction dir);
        void updateVelocity();
        std::array<float, 2> getPosition();
        void rotate(float angle);
        float getAngle();

        //Métodos de disparos/vida
        void activateWeapon();
        void recvDamage(float damage);
        float getHealth();
        float isHitBy(float x, float y, float angle);

        Player(Player&& other);
        Player& operator=(Player&& other);        
};

#endif
