#ifndef _GAME_THREAD_H_
#define _GAME_THREAD_H_

#include "../common_src/Thread.h"
#include "GameProxy.h"

class GameThread: public Thread{
    public:
        GameProxy &game;
}

#endif
