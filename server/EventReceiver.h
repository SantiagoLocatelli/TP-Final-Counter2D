#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include "../common/Thread.h"
#include "../common/Protocol.h"
#include "EventQueue.h"

class EventReceiver: public Thread{
    private:
        Protocol &protocol;
        EventQueue &queue;
        int id;
        bool keep_listening;

        void run();

    public:
        EventReceiver(Protocol &protocol, EventQueue &queue, int id);
        void stop();
};  

#endif
