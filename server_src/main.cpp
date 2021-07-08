#include "Accepter.h"
#include "GameList.h"

int main(int argc, char const *argv[]){
    if (argc != 2)
        return -1;
    
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
