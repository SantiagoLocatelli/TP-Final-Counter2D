#include "Accepter.h"
#include "GameProxy.h"
#include "Emitter.h"
#include "EventQueue.h"
#include "../common_src/Stopwatch.h"

#include <iostream>
#include <chrono>

void executeEvent(GameProxy &game, Event &event, int id){
    //TODO: Hacer con polimorfismo
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

    case CREATE_PLAYER:
        game.createPlayer();
    }    
}

//TODO: Esto va a terminar en su propio hilo (game manager)
int main(int argc, char const *argv[]){
    if (argc != 2)
        return -1;
    try{
        Emitter emitter;
        EventQueue queue;
        GameProxy game("../../server_src/mapa_mediano.yaml");

        
        Accepter accepter(argv[1], queue, emitter);
        accepter.start();

        Stopwatch stopwatch;
        emitter.emitMap(game.getMapInfo());

        while (getchar() != 's'){
            std::this_thread::sleep_for(std::chrono::seconds(1)); 
        }

        do{
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
        } while (!game.ended());

        accepter.stop();
        accepter.join();
    } catch (const std::exception &e){
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}
