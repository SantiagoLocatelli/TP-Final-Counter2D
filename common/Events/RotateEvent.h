#ifndef _ROTATE_EVENT_H_
#define _ROTATE_EVENT_H_

#include "Event.h"
#include <string>

class RotateEvent: public Event{
    private:
        float angle;
    public:
        explicit RotateEvent(float angle); //En grados
        std::string getBinaryRepresentation() override;

        RotateEvent(const RotateEvent&) = delete;
        RotateEvent& operator=(const RotateEvent&) = delete;
};

#endif
