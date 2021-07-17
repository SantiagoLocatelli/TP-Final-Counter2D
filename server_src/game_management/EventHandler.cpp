#include "EventHandler.h"
#include "../../common_src/Event.h"

EventHandler::EventHandler(GameProxy &game):game(game){}

void EventHandler::executeEvent(Event event, int id){
    switch (event.type){
    case TOGGLE_MOVEMENT:
        game.getPlayer(id).toggleMovement(event.info.dir);
        break;
    
    case SET_ANGLE:
        game.getPlayer(id).setAngle(event.info.angle);
        break;
    
    case TOGGLE_WEAPON:
        game.getPlayer(id).toggleWeapon();
        break;
    
    case RELOAD_WEAPON:
        game.getPlayer(id).reloadWeapon();
        break;

    case CHANGE_WEAPON:
        game.getPlayer(id).changeWeapon(event.info.slot);
        break;
    
    case DROP_WEAPON:
        game.getPlayer(id).dropWeapon();
        break;
    
    case TOGGLE_DEFUSE:
        game.getPlayer(id).toggleDefuse();
        break;

    case BUY_WEAPON:
        game.getPlayer(id).buyWeapon(event.info.type);
        break;
    
    default:
        break;
    }
}
