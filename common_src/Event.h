#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>
#include "GameInfo.h"
#include "WeaponUtils.h"
#include "Direction.h"

enum EventType: char {TOGGLE_MOVEMENT, SET_ANGLE, TOGGLE_WEAPON, RELOAD_WEAPON, CHANGE_WEAPON, DROP_WEAPON, CREATE_GAME, JOIN_GAME, LIST_GAMES};

union EventInfo{
    Direction dir; //Para TOGGLE_MOVEMENT
    float angle; //Para SET_ANGLE en radianes
    GameInfo gameInfo; //Para CREATE_GAME y JOIN_GAME
    WeaponSlot slot; //Para CHANGE_WEAPON
};

struct Event{
    EventType type;
    union EventInfo info;
};

#endif
