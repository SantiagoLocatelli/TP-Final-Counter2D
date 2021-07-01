#ifndef _ACTIVATE_WEAPON_EVENT_H_
#define _ACTIVATE_WEAPON_EVENT_H_

#include "Event.h"
#include <string>

class ActivateWeaponEvent: public Event{
    public:
        ActivateWeaponEvent();
        std::string getBinaryRepresentation() override;
        void* getData() override;

        ActivateWeaponEvent(const ActivateWeaponEvent&) = delete;
        ActivateWeaponEvent& operator=(const ActivateWeaponEvent&) = delete;
};

#endif
