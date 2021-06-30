#include "Accepter.h"
#include "GameProxy.h"
#include "Emitter.h"
#include "EventQueue.h"
#include "../common/Stopwatch.h"

#include <chrono>

void executeEvent(GameProxy &game, Event &event, int id){
    if (event == UP_ON || event == UP_OFF){
        game.toggleMovement(id, UP);
    } else if (event == DOWN_ON || event == DOWN_OFF){
        game.toggleMovement(id, DOWN);
    } else if (event == LEFT_ON || event == LEFT_OFF){
        game.toggleMovement(id, LEFT);
    } else if (event == RIGHT_ON || event == RIGHT_OFF){
        game.toggleMovement(id, RIGHT);
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
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        game.step();
        emitter.emitModel(std::move(game.getModelInfo()));
    }

    return 0;
}
