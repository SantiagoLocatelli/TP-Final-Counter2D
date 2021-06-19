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

    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(42));
        gm.step_world(0.042);
        float x, y;
        gm.get_player_position(x, y);
        protocol.send_position(x, y);
    }  

    return 0;
}
