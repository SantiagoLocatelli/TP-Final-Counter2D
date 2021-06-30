#ifndef _TOGGLE_MOVEMENT_EVENT_H_
#define _TOGGLE_MOVEMENT_EVENT_H_

#include "Event.h"
#include <string>

enum Direction {UP, DOWN, LEFT, RIGHT};

class ToggleMovementEvent: public Event{
    private:
        Direction dir;
    public:
        explicit ToggleMovementEvent(Direction dir);
        std::string getBinaryRepresentation() override;

        ToggleMovementEvent(const ToggleMovementEvent&) = delete;
        ToggleMovementEvent& operator=(const ToggleMovementEvent&) = delete;
};

#endif
