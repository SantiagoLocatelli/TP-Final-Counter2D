#ifndef _GAME_LIST_H_
#define _GAME_LIST_H_

#include <list>

struct GameInfo{
    char name[30];
    char map[30];
    int players;
};

struct GameList{
    std::list<GameInfo> games;
};

#endif
