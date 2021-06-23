#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <box2d/box2d.h>
#include <array>


class Player{
    private:
        float health;
        b2Body *body;
        bool dead;

    public:
        Player(b2World &world, float start_x, float start_y);
        void applyImpulse(float x, float y);
        std::array<float, 2> getPosition();
        float isHitBy(float x, float y, float angle);
        void recvDamage(float damage);
        float getHealth();

        Player(Player&& other);
        Player& operator=(Player&& other);        
};

#endif
