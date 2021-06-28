#include "EventQueue.h"

void EventQueue::push(int id, Event event){
    const std::lock_guard<std::mutex> lock(m);
    std::pair<int, Event> p;
    p.first = id;
    p.second = event;
    queue.push(p);
}

bool EventQueue::isEmpty(){
    const std::lock_guard<std::mutex> lock(m);
    return queue.empty();
}

Event EventQueue::pop(int &id){
    const std::lock_guard<std::mutex> lock(m);
    std::pair<int, Event> p = queue.front();
    queue.pop();

    id = p.first;
    return p.second;
}
