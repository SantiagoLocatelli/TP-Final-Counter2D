#include "EventHandler.h"
#include "../../common_src/Event.h"

EventHandler::EventHandler(GameProxy &game):game(game){}

void EventHandler::executeEvent(Event event, int id){
    switch (event.type){
    case TOGGLE_MOVEMENT:
        game.toggleMovement(id, event.info.dir);
        break;
    
    case SET_ANGLE:
        game.setAngle(id, event.info.angle);
        break;
    
    case TOGGLE_WEAPON:
        game.toggleWeapon(id);
        break;
    
    case RELOAD_WEAPON:
        game.reloadWeapon(id);
        break;

    case CHANGE_WEAPON:
        game.changeWeapon(id, event.info.slot);
        break;
    
    case DROP_WEAPON:
        game.dropWeapon(id);
        break;
    
    case TOGGLE_DEFUSE:
        game.toggleDefuse(id);
        break;

    case BUY_WEAPON:
        game.buyWeapon(id, event.info.type);
        break;
    
    default:
        break;
    }
}