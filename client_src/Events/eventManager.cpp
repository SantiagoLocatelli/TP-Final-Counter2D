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
                            case SDLK_e: 
                                event.type = TOGGLE_DEFUSE;
                                break;
                            case SDLK_r:
                                event.type = RELOAD_WEAPON;
                                break;
                            case SDLK_1: 
                                event.type = CHANGE_WEAPON;
                                event.info.slot = KNIFE_SLOT;
                                break;
                            case SDLK_2:
                                event.type = CHANGE_WEAPON;
                                event.info.slot = SECONDARY;
                                break;
                            case SDLK_3:
                                event.type = CHANGE_WEAPON;
                                event.info.slot = PRIMARY;
                                break;
                            case SDLK_4:
                                event.type = CHANGE_WEAPON;
                                event.info.slot = BOMB_SLOT;
                                break;
                            case SDLK_g:
                                event.type = DROP_WEAPON;
                                break;
                        }

                        this->com.send_event(event);
                    }
                    break; 

                /**<SDL_MouseButtonEvent ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
                case SDL_MOUSEBUTTONUP: 
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
                    Coordinate pos = game.mainPlayerRelativePos();
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