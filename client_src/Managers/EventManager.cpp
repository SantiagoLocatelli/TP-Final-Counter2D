#include "EventManager.h"
#include "GameMath.h"
#include "../../common_src/SocketClosedException.h"
#include <iostream>

EventManager::EventManager(Protocol& com, bool& gameEnded, GameViewer& game):com(com), gameEnded(gameEnded), game(game){}

void EventManager::run(){
    try{
        SDL_Event e;
        while (!gameEnded && SDL_WaitEvent(&e) != 0){
            Event event;
            switch (e.type) {
                case SDL_QUIT:
                    this->gameEnded = true; 
                    break;

                //Ambos casos hacen lo mismo
                case SDL_KEYUP:
                case SDL_KEYDOWN:
                    if (e.key.repeat == 0){
                        switch ( e.key.keysym.sym ){
                            case SDLK_w: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = UP; 
                                this->com.send_event(event);
                                break;
                            case SDLK_s: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = DOWN; 
                                this->com.send_event(event);
                                break;
                            case SDLK_a: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = LEFT; 
                                this->com.send_event(event);
                                break;
                            case SDLK_d: 
                                event.type = TOGGLE_MOVEMENT;
                                event.info.dir = RIGHT; 
                                this->com.send_event(event);
                                break;
                            case SDLK_e: 
                                event.type = TOGGLE_DEFUSE;
                                this->com.send_event(event);
                                break;
                            case SDLK_r:
                                event.type = RELOAD_WEAPON;
                                this->com.send_event(event);
                                break;
                            case SDLK_1: 
                                event.type = CHANGE_WEAPON;
                                event.info.slot = KNIFE_SLOT;
                                this->com.send_event(event);
                                break;
                            case SDLK_2:
                                event.type = CHANGE_WEAPON;
                                event.info.slot = SECONDARY;
                                this->com.send_event(event);
                                break;
                            case SDLK_3:
                                event.type = CHANGE_WEAPON;
                                event.info.slot = PRIMARY;
                                this->com.send_event(event);
                                break;
                            case SDLK_4:
                                event.type = CHANGE_WEAPON;
                                event.info.slot = BOMB_SLOT;              
                                this->com.send_event(event);
                                break;
                            case SDLK_8:
                                event.type = BUY_WEAPON;
                                event.info.type = SNIPER;
                                this->com.send_event(event);
                                break;
                            case SDLK_9:
                                event.type = BUY_WEAPON;
                                event.info.type = SHOTGUN;
                                this->com.send_event(event);
                                break;
                            case SDLK_0:
                                event.type = BUY_WEAPON;
                                event.info.type = RIFLE;
                                this->com.send_event(event);
                                break;
                            case SDLK_g:
                                event.type = DROP_WEAPON;
                                this->com.send_event(event);
                                break;
                        }
                    }
                    break; 

                /**<SDL_MouseButtonEvent ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
                case SDL_MOUSEBUTTONUP: 
                case SDL_MOUSEBUTTONDOWN:
                    switch (e.button.button){
                        case SDL_BUTTON_LEFT:
                            event.type = TOGGLE_WEAPON;
                            this->com.send_event(event);
                            break;
                    }
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
    } catch(const SocketClosedException &e){
        //Si me cierran el socket no quiero imprimir error. Es esperado.
    } catch (const std::exception &e){
        std::cerr << "ERROR en `EventManager`: " << e.what() << std::endl;
    }
}

void EventManager::stop(){
    SDL_Event e;
    e.type = SDL_QUIT;
    SDL_PushEvent(&e);
}