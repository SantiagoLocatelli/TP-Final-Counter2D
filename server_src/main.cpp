#include "communications/Accepter.h"
#include "game_management/GameList.h"
#include <iostream>

int main(int argc, char const *argv[]){
    if (argc != 2){
        std::cout << "Cantidad incorrecta de argumentos.\n";
        return -1;
    }
    
    GameList gameList;
    Accepter accepter(argv[1], gameList);
    accepter.start();

    while (getchar() != 'q'){
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }

    accepter.stop();
    accepter.join();

    return 0;
}
