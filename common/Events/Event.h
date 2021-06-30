#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>

class Event{
    public:
        virtual std::string getBinaryRepresentation() = 0;
        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;
};

#endif
