#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "Socket.h"
#include <stdint.h>
#define DEC_SENT 2

enum Event : char {UP_ON, UP_OFF, DOWN_ON, DOWN_OFF, RIGHT_ON, RIGHT_OFF
, LEFT_ON, LEFT_OFF};

class Protocol{
    private:
        Socket skt;
        
        //Envía un short por el socket. 
        void send_short(const uint16_t buf);
        //Recibe un short por el socket.
        void recv_short(uint16_t &buf);

        void send_byte(const char byte);
        void recv_byte(char& byte);

    public:
        explicit Protocol(Socket skt);

        //TODO:Estos son temporales, hay que sacarlos
        void send_window_size(const uint16_t length, const uint16_t height);
        void recv_window_size(uint16_t &length, uint16_t &height);
        void send_pixel_position(const uint16_t x, const uint16_t y);
        void recv_pixel_position(uint16_t &x, uint16_t &y);

        //Envía una posicion por el socket. Solo se envían los primeros 
        //DEC_SENT decimales, el resto se pierde.
        void send_position(const float x, const float y);
        //Recibe una posicion por el socket.
        void recv_position(float &x, float &y);

        //Envía un evento por el socket.
        void send_event(const Event event);
        //Recibe un evento por el socket.
        void recv_event(Event &event);

        Protocol(const Protocol&) = delete;
        Protocol& operator=(const Protocol&) = delete;
};

#endif
