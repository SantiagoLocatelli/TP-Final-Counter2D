#include "EventReceiver.h"
#include <iostream>

EventReceiver::EventReceiver(GameManager &game, Protocol &protocol)
:game(game), keep_listening(true), protocol(protocol){}

void EventReceiver::run(){
    Event event;
    while (keep_listening){
        protocol.recv_event(event);
        std::cout << "Llego el evento: " << event << std::endl;
        //TODO: Hacerlo con polimorfismo
        if (event == UP_ON || event == UP_OFF){
            game.move_player(UP);
        } else if (event == DOWN_ON || event == DOWN_OFF){
            game.move_player(DOWN);
        } else if (event == LEFT_ON || event == LEFT_OFF){
            game.move_player(LEFT);
        } else if (event == RIGHT_ON || event == RIGHT_OFF){
            game.move_player(RIGHT);
        }
    }
}

void EventReceiver::start(){
    thread = std::thread(&EventReceiver::run, this);
}

void EventReceiver::stop(){
    //TODO: Este metodo asi como esta no funciona porque el recv es bloqueante
    keep_listening = false;
}

void EventReceiver::join(){
    thread.join();
}
