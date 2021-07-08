#ifndef _GAME_INFO_H_
#define _GAME_INFO_H_

#include <stdint.h>

struct GameInfo{
    char name[30];
    char map[30];
    uint16_t players;
    uint16_t max_players;
};

#endif
