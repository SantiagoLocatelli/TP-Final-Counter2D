#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "../game_model/World.h"
#include "../game_model/Player.h"

#include <mutex>

enum Direction {UP, DOWN, LEFT, RIGHT};

class GameManager{
    private:
        std::mutex m;
        World* world;
        Player* player;
    
    public:
        explicit GameManager(char *yaml_file);

        void move_player(Direction dir);
        void get_player_position(float &x, float &y);

        void step_world();

        ~GameManager();
};

#endif
