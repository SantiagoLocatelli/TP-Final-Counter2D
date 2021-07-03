#include "EventReceiver.h"
#include "../common_src/SocketClosedException.h"
#include <iostream>

EventReceiver::EventReceiver(Protocol &protocol, EventQueue &queue, int id)
:protocol(protocol), queue(queue), id(id), keep_listening(true){}

void EventReceiver::run(){
    while (keep_listening){
        Event event;
        try{
            protocol.recv_event(event);
            queue.push(id, event);
        } catch (const SocketClosedException &e){
            keep_listening = false;
        } catch (const std::exception &e){
            std::cerr << "Error en EventReceiver:" << e.what() << std::endl;
        }
    }
}

void EventReceiver::stop(){
    keep_listening = false;
    protocol.close();
}
