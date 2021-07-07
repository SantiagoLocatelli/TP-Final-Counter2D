#include "eventManager.h"
#include "gameMath.h"
#include <iostream>

EventManager::EventManager(Protocol& com, bool& quit, GameViewer& game):com(com), quit(quit), game(game){}

void EventManager::run(){
    try{
        SDL_Event e;
        while (!quit && SDL_WaitEvent(&e) != 0){
            Event event;
            switch (e.type) {
                case SDL_QUIT:
                    this->quit = true; 
                    break;

                //Ambos casos hacen lo mismo
                case SDL_KEYUP:
                case SDL_KEYDOWN:
                    if (e.key.repeat == 0){
                        switch ( e.key.keysym.sym ){
                            case SDLK_w: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = UP; 
                                break;
                            case SDLK_s: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = DOWN; 
                                break;
                            case SDLK_a: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = LEFT; 
                                break;
                            case SDLK_d: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = RIGHT; 
                                break;
                            case SDLK_e: /*plantar bomba*/break;
                            case SDLK_r: /*recargar*/break;
                            case SDLK_1: /*cambiar arma a 1*/break;
                            case SDLK_2: /*cambiar arma a 2*/break;
                            case SDLK_3: /*cambiar arma a 3*/break;
                            case SDLK_4: /*cambiar arma a 4*/break;
                            case SDLK_g: /*dropear arma*/break;
                        }

                        this->com.send_event(event);
                    }
                    break; 

                /**<SDL_MouseButtonEvent ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
                //case SDL_MOUSEBUTTONUP: Por ahora solo cuando apreta el boton 
                case SDL_MOUSEBUTTONDOWN:
                    switch (e.button.button){
                        case SDL_BUTTON_LEFT:
                            event.type = TOGGLE_WEAPON;
                            break;
                        case SDL_BUTTON_RIGHT:
                            // apuntar con mira o cambiar modo
                            break;
                        case SDL_BUTTON_MIDDLE:
                            // cualquier que se les ocurra
                            break;
                    }
                    this->com.send_event(event);
                    break;
                case SDL_MOUSEMOTION:
                    Coordenada pos = game.mainPlayerRelativePos();
                    float radians = Math::calculateRadians({pos.x, pos.y}, {e.motion.x, e.motion.y});
                    game.setCrossHair({e.motion.x, e.motion.y});
                    event.type = SET_ANGLE;
                    event.info.angle = radians;
                    this->com.send_event(event);
            }
        }

        com.close();
    } catch (const std::exception &e){
        std::cerr << "ERROR en `EventManager`: " << e.what() << std::endl;
    }
}

void EventManager::stop(){
    SDL_Event e;
    e.type = SDL_QUIT;
    SDL_PushEvent(&e);
}