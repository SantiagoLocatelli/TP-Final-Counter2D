#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../GameViewer.h"
#include "../../common_src/Thread.h"
#include <SDL2/SDL.h>
#include "../../common_src/Protocol.h"

class EventManager : public Thread{
private:
    Protocol& com;
    bool& quit;
    GameViewer& game;

public:

    EventManager(Protocol& com, bool& quit, GameViewer& game);
    EventManager();
    ~EventManager() = default;

    void run() override;
    void stop();

    EventManager& operator=(const EventManager&) = delete;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(EventManager&& other) = delete;
};

#endif