#include "Accepter.h"
#include "GameProxy.h"
#include "Emitter.h"
#include "EventQueue.h"
#include "../common/Stopwatch.h"

#include <chrono>

void executeEvent(Event event){
}

//TODO: Esto va a terminar en su propio hilo (game manager)
int main(int argc, char const *argv[]){
    if (argc != 2)
        return -1;
    
    Emitter emitter;
    EventQueue queue;
    GameProxy game("map.yaml");

    //TODO: Agarrado con alambres. Solo para la prueba 
    game.createPlayer(1);
    game.createPlayer(2);

    emitter.emitMap(game.getMapInfo());
    
    Accepter accepter(argv[1], queue, emitter);

    Stopwatch stopwatch;
    while (!game.ended()){
        stopwatch.start();
        while (stopwatch.msPassed() < 33){
            //TODO: Sacar este busy wait
            if (!queue.isEmpty()){
                executeEvent(queue.pop());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        game.step();
        emitter.emitModel(game.getModelInfo());
    }

    return 0;
}
