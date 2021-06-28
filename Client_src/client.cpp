#include "client.h"
#include "../protocol/Socket.h"
#include <utility>

Client::Client(const char* host, const char* service):
    com(std::move(Socket(host, service, false))){
}


void Client::recvMapInfo(MapInfo& map){this->com.recv_map_info(map);}
void Client::recvModelInfo(ModelInfo& model){this->com.recv_model_info(model);}


// enum Event : char {UP_ON, UP_OFF, DOWN_ON, DOWN_OFF, RIGHT_ON, RIGHT_OFF
// , LEFT_ON, LEFT_OFF};

void Client::sendEvent(const SDL_Event& e){

	switch (e.type) {
        case SDL_KEYDOWN:
            if (e.key.repeat == 0){
                //Adjust the velocity
                switch( e.key.keysym.sym ){
                    case SDLK_UP: this->com.send_event(UP_ON); break;
                    case SDLK_DOWN: this->com.send_event(DOWN_ON); break;
                    case SDLK_LEFT: this->com.send_event(LEFT_ON); break;
                    case SDLK_RIGHT: this->com.send_event(RIGHT_ON); break;
                }
            }
            break;
        //If a key was released
        case SDL_KEYUP:

            if(e.key.repeat == 0 ){
                //Adjust the velocity
                switch( e.key.keysym.sym ){
                    case SDLK_UP:this->com.send_event(UP_OFF); break;
                    case SDLK_DOWN: this->com.send_event(DOWN_OFF); break;
                    case SDLK_LEFT: this->com.send_event(LEFT_OFF); break;
                    case SDLK_RIGHT: this->com.send_event(RIGHT_OFF); break;
                }
            }
            break;
    }
}