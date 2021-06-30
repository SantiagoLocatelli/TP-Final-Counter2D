#include "eventManager.h"

// EventManager::EventManager(Protocol& com):com(com){}

EventManager::EventManager(){}

void EventManager::handleEvent(Character& pj, SDL_Event& e){

    //If a key was pressed
	switch (e.type) {
        case SDL_KEYDOWN:
            if (e.key.repeat == 0 ){
                //Adjust the velocity
                switch( e.key.keysym.sym ){
                    case SDLK_UP: pj.moveUp(); break;
                    case SDLK_DOWN: pj.moveDown(); break;
                    case SDLK_LEFT: pj.moveLeft(); break;
                    case SDLK_RIGHT: pj.moveRight(); break;
                }
            }
            break;
        //If a key was released
        case SDL_KEYUP:

            if(e.key.repeat == 0 ){
                //Adjust the velocity
                switch( e.key.keysym.sym ){
                    case SDLK_UP: pj.stopUp(); break;
                    case SDLK_DOWN: pj.stopDown(); break;
                    case SDLK_LEFT: pj.stopLeft(); break;
                    case SDLK_RIGHT: pj.stopRight(); break;
                }
            }
            break;
        case SDL_MOUSEMOTION: 
            pj.lookAt(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            break;
        
    }
}

// void EventManager::run(){

//     SDL_Event e;
//     while (SDL_WaitEvent(&e) != 0){
//         switch (e.type) {
//             case SDL_KEYDOWN:
//                 if (e.key.repeat == 0){
//                     switch( e.key.keysym.sym ){
//                         case SDLK_w: this->com.send_event(UP_ON); break;
//                         case SDLK_s: this->com.send_event(DOWN_ON); break;
//                         case SDLK_a: this->com.send_event(LEFT_ON); break;
//                         case SDLK_d: this->com.send_event(RIGHT_ON); break;
//                         case SDLK_e: /*plantar bomba*/break;
//                         case SDLK_r: /*recargar*/break;
//                         case SDLK_1: /*cambiar arma a 1*/break;
//                         case SDLK_2: /*cambiar arma a 2*/break;
//                         case SDLK_3: /*cambiar arma a 3*/break;
//                         case SDLK_4: /*cambiar arma a 4*/break;
//                         case SDLK_g: /*dropear arma*/break;
//                     }
//                 }
//                 break;

//             case SDL_KEYUP:
//                 if(e.key.repeat == 0){
//                     //Adjust the velocity
//                     switch( e.key.keysym.sym ){
//                         case SDLK_w:this->com.send_event(UP_OFF); break;
//                         case SDLK_s: this->com.send_event(DOWN_OFF); break;
//                         case SDLK_a: this->com.send_event(LEFT_OFF); break;
//                         case SDLK_d: this->com.send_event(RIGHT_OFF); break;
//                     }
//                 }
//                 break;
                

//             /**<SDL_MouseButtonEvent ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
//             case SDL_MOUSEBUTTONDOWN: 
//                 switch (e.button.button){
//                     case SDL_BUTTON_LEFT:
//                         // disparar
//                         break;
//                     case SDL_BUTTON_RIGHT:
//                         // apuntar con mira o cambiar modo
//                         break;
//                     case SDL_BUTTON_MIDDLE:
//                         // cualquier que se les ocurra
//                         break;
//                 }
//                 break;

//             case SDL_MOUSEBUTTONUP:
//                 switch (e.button.button){
//                     case SDL_BUTTON_LEFT:
//                         // dejar de disparar
//                         break;
//                     case SDL_BUTTON_RIGHT: // nose
//                         // apuntar con mira o cambiar modo
//                         break;
//                     case SDL_BUTTON_MIDDLE: // nose
//                         // cualquier que se les ocurra
//                         break;
//                 }
//                 break;
            
//         }
//     }
    
// }