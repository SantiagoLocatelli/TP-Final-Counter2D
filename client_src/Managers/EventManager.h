#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "../../common_src/Protocol.h"
#include "../../common_src/Thread.h"
#include "GameViewer.h"
#include <SDL2/SDL.h>

class EventManager : public Thread{
private:
    Protocol& com;
    bool& gameEnded;
    GameViewer& game;

public:

    EventManager(Protocol& com, bool& gameEnded, GameViewer& game);
    EventManager();
    ~EventManager() = default;

    void run() override;

    EventManager& operator=(const EventManager&) = delete;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(EventManager&& other) = delete;
};

#endif