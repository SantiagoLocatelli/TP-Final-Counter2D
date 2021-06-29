#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../Character/character.h"
#include "../../common/Thread.h"
#include <SDL2/SDL.h>
#include "../../common/Protocol.h"

class EventManager: public Thread{
private:
    Protocol& com;

public:

    EventManager(Protocol& com);
    ~EventManager();

    //void handleEvent(Character& pj, SDL_Event& e);
    void start();
    void run() override;

    EventManager& operator=(const EventManager&) = delete;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(EventManager&& other) = delete;
};

#endif