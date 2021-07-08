#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "Socket.h"
#include <stdint.h>
#include <list>
#include "GameInfo.h"
#include "MapInfo.h"
#include "ModelInfo.h"
#include "Event.h"

#define DEC_SENT 2

class Protocol{
    private:
        Socket skt;
        
        //Envía un short por el socket. 
        void send_short(const uint16_t &buf);
        //Recibe un short por el socket.
        void recv_short(uint16_t &buf);

        void send_byte(const char &byte);
        void recv_byte(char &byte);

        void send_bool(const bool &b);
        void recv_bool(bool &b);

        //Envía un float por el socket. Solo se envían los primeros 
        //DEC_SENT decimales, el resto se pierde.
        void send_float(const float &f);
        void recv_float(float &f);
    
    public:
        explicit Protocol(Socket skt);
        Protocol(Protocol&& other); 
        
        void send_map_info(const MapInfo &mapInfo);
        void recv_map_info(MapInfo &mapInfo);

        void send_model_info(const ModelInfo &modelInfo);
        void recv_model_info(ModelInfo &modelInfo);

        void send_game_list(const std::list<GameInfo> &gameList);
        void recv_game_list(std::list<GameInfo> &gameList);

        void send_event(const Event event);
        void recv_event(Event &event);

        void close();

        Protocol(const Protocol&) = delete;
        Protocol& operator=(const Protocol&) = delete;
};

#endif
