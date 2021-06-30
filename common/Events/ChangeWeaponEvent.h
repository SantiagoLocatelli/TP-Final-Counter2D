#ifndef _CHANGE_WEAPON_EVENT_H_
#define _CHANGE_WEAPON_EVENT_H_

#include "Event.h"
#include <string>

enum Weapon {KNIFE, SECONDARY, PRIMARY, BOMB};

class ChangeWeaponEvent: public Event{
    public:
        explicit ChangeWeaponEvent(Weapon weapon);
        std::string getBinaryRepresentation() override;

        ChangeWeaponEvent(const ChangeWeaponEvent&) = delete;
        ChangeWeaponEvent& operator=(const ChangeWeaponEvent&) = delete;
};

#endif
