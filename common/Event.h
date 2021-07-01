#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>
#include "Direction.h"

enum EventType: char {TOGGLE_MOVEMENT, SET_ANGLE, ACTIVATE_WEAPON};

union EventInfo{
    Direction dir;
    float angle; //En radianes
};

struct Event{
    EventType type;
    union EventInfo info;
};

#endif
