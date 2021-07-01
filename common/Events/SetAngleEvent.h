#ifndef _SET_ANGLE_EVENT_H_
#define _SET_ANGLE_EVENT_H_

#include "Event.h"
#include <string>

class SetAngleEvent: public Event{
    private:
        float angle;
    public:
        explicit SetAngleEvent(float angle); //En grados
        std::string getBinaryRepresentation() override;
        void* getData() override;

        SetAngleEvent(const SetAngleEvent&) = delete;
        SetAngleEvent& operator=(const SetAngleEvent&) = delete;
};

#endif
