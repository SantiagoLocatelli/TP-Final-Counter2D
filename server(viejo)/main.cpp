#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include "GameManager.h"
#include "../protocol/Protocol.h"
#include "EventReceiver.h"

#define TAM_MAPA 5.0
uint16_t length, height; //TODO: Sacar estas variables globales.

void convert_to_pixels(float x, float y, uint16_t &pixel_x, uint16_t &pixel_y){
    pixel_x = (x/TAM_MAPA)*(float)length;
    pixel_y = (y/TAM_MAPA)*(float)height;
}


int main(){
    Socket acceptador(NULL, "8081", true);
    Protocol protocol(acceptador.accept_one());
    GameManager gm("mapa.yaml");
    EventReceiver receiver(gm, protocol);

    protocol.recv_window_size(length, height);
    receiver.start();

    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
        gm.step_world();
        float x, y;
        gm.get_player_position(x, y);
        std::cout << "x = " << x << ", y = " << y << std::endl;
        uint16_t pixel_x, pixel_y;
        convert_to_pixels(x,y,pixel_x,pixel_y);
        protocol.send_pixel_position(pixel_x, pixel_y);
    }  

    return 0;
}
