#include "EventReceiver.h"
#include <iostream>

EventReceiver::EventReceiver(Protocol &protocol, EventQueue &queue, int id)
:protocol(protocol), queue(queue), id(id), keep_listening(true){}

void EventReceiver::run(){
    while (keep_listening){
        Event event;
        protocol.recv_event(event);
        queue.push(id, event);
    }
}

void EventReceiver::stop(){
    keep_listening = false;
    protocol.close();
}
