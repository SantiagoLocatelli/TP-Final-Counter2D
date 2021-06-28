#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../common/Protocol.h"
#include "SDL2/SDL.h"

class Client{
private:
    Protocol com;

public:
    Client(const char* host, const char* service);

    void recvMapInfo(MapInfo& map);
    void recvModelInfo(ModelInfo& model);
    void sendEvent(const SDL_Event& e);
};

#endif