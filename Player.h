#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <box2d/box2d.h>


class Player{
    private:
        b2Body *body;

    public:
        Player(b2World &world, float start_x, float start_y);
        void applyImpulse(float x, float y);
        b2Vec2 getPosition();
};

#endif
