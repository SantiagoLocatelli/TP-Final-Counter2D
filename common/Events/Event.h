#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>

class Event{
    private:
        char eventByte;

    public:
        explicit Event(char eventByte);
        
        virtual std::string getBinaryRepresentation() = 0;
        char getEventByte();
        virtual void* getData() = 0;

        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;
};

#endif
