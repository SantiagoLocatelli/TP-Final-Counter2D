#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include "GameManager.h"
#include "protocol/Protocol.h"
#include "EventReceiver.h"

int main(){
    Socket acceptador(NULL, "8080", true);
    Protocol protocol(acceptador.accept_one());
    GameManager gm("mapa.yaml");
    EventReceiver receiver(gm, protocol);

    // for (int i = 0; i < 25; i++){
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     world.step(0.5);
    //     b2Vec2 position = p.getPosition();
    //     printf("Jugador:\n\tx:%4.2f\n\ty:%4.2f\n", position.x, position.y); 
    // }  

    return 0;
}
