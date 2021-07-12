#include "CollisionHandler.h"

#include "Player.h"
#include "Drop.h"

void CollisionHandler::BeginContact(b2Contact* contact){
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();

    if (bodyA->GetUserData().pointer && bodyB->GetUserData().pointer){
        //Esto significa que es una colision entre jugadores/cajas
        return;
    }

    Player *player;
    Drop *drop;
    if (bodyA->GetUserData().pointer){
        //TODO: Faltaria chequear que no es una caja
        player = (Player *)bodyA->GetUserData().pointer;
        drop = (Drop *)bodyB->GetFixtureList()->GetUserData().pointer;
    } else {
        player = (Player *)bodyB->GetUserData().pointer;
        drop = (Drop *)bodyA->GetFixtureList()->GetUserData().pointer;
    }
    
    if (player->canTake(drop->getWeapon())){
        player->takeWeapon(drop->getTaken());
    }
}
