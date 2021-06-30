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
        EventQueue() = default;
        void push(int id, Event event);
        bool isEmpty();
        Event pop(int &id);

        EventQueue(const EventQueue&) = delete;
        EventQueue& operator=(const EventQueue&) = delete;
};

#endif
