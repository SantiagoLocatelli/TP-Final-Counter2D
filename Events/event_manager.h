#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../Character/character.h"
#include <SDL2/SDL.h>

class EventManager{
private:

public:

    EventManager();
    void handleEvent(Character& pj, SDL_Event& e);
};

#endif