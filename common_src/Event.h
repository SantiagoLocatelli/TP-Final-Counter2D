#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>
#include "Direction.h"

enum EventType: char {TOGGLE_MOVEMENT, SET_ANGLE, TOGGLE_WEAPON, CREATE_PLAYER};

union EventInfo{
    Direction dir; //Para TOGGLE_MOVEMENT
    float angle; //Para SET_ANGLE en radianes
};

struct Event{
    EventType type;
    union EventInfo info;
};

#endif
