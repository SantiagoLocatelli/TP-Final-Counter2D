#include "Accepter.h"
#include "GameProxy.h"
#include "Emitter.h"
#include "EventQueue.h"
#include "../common_src/Stopwatch.h"

#include <chrono>

void executeEvent(GameProxy &game, Event &event, int id){
    //TODO: Hacer con un MapExecuter
    switch (event.type){
    case TOGGLE_MOVEMENT:
        game.toggleMovement(id, event.info.dir);
        break;
    
    case SET_ANGLE:
        game.setAngle(id, event.info.angle);
    
    case TOGGLE_WEAPON:
        game.toggleWeapon(id);
    }    
}

//TODO: Esto va a terminar en su propio hilo (game manager)
int main(int argc, char const *argv[]){
    if (argc != 2)
        return -1;
    
    Emitter emitter;
    EventQueue queue;
    GameProxy game("mapa.yaml");

    //TODO: Agarrado con alambres. Solo para la prueba 
    game.createPlayer(1);
    //game.createPlayer(2);

    emitter.emitMap(game.getMapInfo());
    
    Accepter accepter(argv[1], queue, emitter);
    accepter.start();

    Stopwatch stopwatch;

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
    }

    return 0;
}
