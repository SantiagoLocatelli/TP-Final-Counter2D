#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../Character/character.h"
#include "../../common_src/Thread.h"
#include <SDL2/SDL.h>
#include "../../common_src/Protocol.h"

class EventManager : public Thread{
private:
    Protocol& com;
    bool& quit;
    Character& pj;

public:

    EventManager(Protocol& com, bool& quit, Character& pj);
    EventManager();
    ~EventManager() = default;

    void run() override;

    EventManager& operator=(const EventManager&) = delete;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(EventManager&& other) = delete;
};

#endif