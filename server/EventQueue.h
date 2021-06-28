#ifndef _EVENT_QUEUE_H_
#define _EVENT_QUEUE_H_

#include "../common/Event.h"
#include <mutex>
#include <utility>
#include <queue>

class EventQueue{
    private:
        std::mutex m;
        std::queue<std::pair<int, Event>> queue;

    public:
        void push(int id, Event event);
        bool isEmpty();
        Event pop(int &id);
};

#endif
