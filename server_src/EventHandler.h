#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include "GameProxy.h"

class EventHandler{
    private:
        GameProxy &game;
    
    public:
        explicit EventHandler(GameProxy &game);
        void executeEvent(Event event, int id);
};

#endif
