#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "Socket.h"
#include <stdint.h>
#include "MapInfo.h"
#include "ModelInfo.h"
#define DEC_SENT 2

enum Event : char {UP_ON, UP_OFF, DOWN_ON, DOWN_OFF, RIGHT_ON, RIGHT_OFF
, LEFT_ON, LEFT_OFF};

class Protocol{
    private:
        Socket skt;
        
        //Envía un short por el socket. 
        void send_short(const uint16_t &buf);
        //Recibe un short por el socket.
        void recv_short(uint16_t &buf);

        void send_byte(const char &byte);
        void recv_byte(char& byte);

        //Envía una posicion por el socket. Solo se envían los primeros 
        //DEC_SENT decimales, el resto se pierde.
        void send_position(const float &x, const float &y);
        //Recibe una posicion por el socket.
        void recv_position(float &x, float &y);
    
    public:
        explicit Protocol(Socket skt);

        //TODO:Estos son temporales, hay que sacarlos

        void send_map_info(const MapInfo &mapInfo);
        void recv_map_info(MapInfo &mapInfo);

        void send_model_info(const ModelInfo &modelInfo);
        void recv_model_info(ModelInfo &modelInfo);


        //Envía un evento por el socket.
        void send_event(const Event event);
        //Recibe un evento por el socket.
        void recv_event(Event &event);

        Protocol(const Protocol&) = delete;
        Protocol& operator=(const Protocol&) = delete;
};

#endif
