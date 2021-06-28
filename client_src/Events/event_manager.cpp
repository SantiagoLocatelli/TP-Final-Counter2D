#include "event_manager.h"

EventManager::EventManager(Protocol& com): com(com){}

// void EventManager::handleEvent(Character& pj, SDL_Event& e){

//     //If a key was pressed
// 	switch (e.type) {
//         case SDL_KEYDOWN:
//             if (e.key.repeat == 0 ){
//                 //Adjust the velocity
//                 switch( e.key.keysym.sym ){
//                     case SDLK_UP: pj.moveUp(); break;
//                     case SDLK_DOWN: pj.moveDown(); break;
//                     case SDLK_LEFT: pj.moveLeft(); break;
//                     case SDLK_RIGHT: pj.moveRight(); break;
//                 }
//             }
//             break;
//         //If a key was released
//         case SDL_KEYUP:

//             if(e.key.repeat == 0 ){
//                 //Adjust the velocity
//                 switch( e.key.keysym.sym ){
//                     case SDLK_UP: pj.stopUp(); break;
//                     case SDLK_DOWN: pj.stopDown(); break;
//                     case SDLK_LEFT: pj.stopLeft(); break;
//                     case SDLK_RIGHT: pj.stopRight(); break;
//                 }
//             }
//             break;
//         case SDL_MOUSEMOTION: 
//             pj.lookAt(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
//             break;
        
//     }
// }

void EventManager::run(){

    SDL_Event e;
    while (SDL_WaitEvent(&e) != 0){
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
    
}