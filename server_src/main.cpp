#include "Accepter.h"
#include "GameProxy.h"
#include "Emitter.h"
#include "EventQueue.h"
#include "../common_src/Stopwatch.h"

#include <iostream>
#include <chrono>

void executeEvent(GameProxy &game, Event &event, int id){
    //TODO: Hacer con un MapExecuter
    switch (event.type){
    case TOGGLE_MOVEMENT:
        game.toggleMovement(id, event.info.dir);
        break;
    
    case SET_ANGLE:
        game.setAngle(id, event.info.angle);
        break;
    
    case TOGGLE_WEAPON:
        game.toggleWeapon(id);
        break;
    }    
}

//TODO: Esto va a terminar en su propio hilo (game manager)
int main(int argc, char const *argv[]){
    if (argc != 2)
        return -1;
    try{
        Emitter emitter;
        EventQueue queue;
        GameProxy game("../../server_src/mapa.yaml");

        //TODO: Agarrado con alambres. Solo para la prueba 
        game.createPlayer(1);
        game.createPlayer(2);

        
        Accepter accepter(argv[1], queue, emitter);
        accepter.start();

        Stopwatch stopwatch;
        emitter.emitMap(game.getMapInfo());

        //std::this_thread::sleep_for(std::chrono::seconds(60));

        while (!game.ended()){
            stopwatch.start();
            while (stopwatch.msPassed() < 33){
                //TODO: Sacar este busy wait
                if (!queue.isEmpty()){
                    int id;
                    Event event = queue.pop(id);
                    executeEvent(game, event, id);
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }

            game.step();
            emitter.emitModel(std::move(game.getModelInfo()));
            game.clearFrameEvents();
        }
        
        accepter.stop();
        accepter.join();
    } catch (const std::exception &e){
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}
