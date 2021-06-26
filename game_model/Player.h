#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <box2d/box2d.h>
#include <array>
#include <map>

enum Direction {UP, DOWN, LEFT, RIGHT};

class Player{
    private:
        float health;
        b2Body *body;
        bool dead;
        std::map<Direction, bool> movement;

    public:
        Player(b2World &world, float start_x, float start_y);
        void toggle_movement(Direction dir);
        void update_velocity();
        std::array<float, 2> getPosition();
        float isHitBy(float x, float y, float angle);
        void recvDamage(float damage);
        float getHealth();

        Player(Player&& other);
        Player& operator=(Player&& other);        
};

#endif
