#include "../Player.h"
#include "../World.h"

#include <iostream>


int main(){
    World w(5,5);
    Player &p1 = w.createPlayer(0,0);
    Player &p2 = w.createPlayer(2,0);

    p1.applyImpulse(4, 0);

    std::cout << "Player 1: x= " << p1.getPosition()[0] << " - y= " << p1.getPosition()[1] << std::endl;
    std::cout << "Player 2: x= " << p2.getPosition()[0] << " - y= " << p2.getPosition()[1] << std::endl;

    for (int i = 0; i < 30; i++){
        w.step();
        std::cout << "Player 1: x= " << p1.getPosition()[0] << " - y= " << p1.getPosition()[1] << std::endl;
        std::cout << "Player 2: x= " << p2.getPosition()[0] << " - y= " << p2.getPosition()[1] << std::endl;
    }

    return 0;
}