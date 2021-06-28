#include "Protocol.h"
#include <arpa/inet.h>
#include <utility>
#include <cmath>

Protocol::Protocol(Socket skt):skt(std::move(skt)){}

void Protocol::send_short(const uint16_t &buf){
    uint16_t ns = htons(buf);
    skt.send_buffer((char *)&ns, 2);
}

void Protocol::recv_short(uint16_t &buf){
    uint16_t ns;
    skt.recv_buffer((char *)&ns, 2);

    buf = ntohs(ns);
}

void Protocol::send_byte(const char &byte){
    skt.send_buffer(&byte, 1);
}

void Protocol::recv_byte(char &byte){
    skt.recv_buffer(&byte, 1);
}

void Protocol::send_position(const float &x, const float &y){
    //TODO: Chequear que la parte entera de los float se pueda enviar.

    uint16_t n;
    n = std::floor(x*std::pow(10,DEC_SENT));
    send_short(n);

    n = std::floor(y*std::pow(10,DEC_SENT));
    send_short(n);
}

void Protocol::recv_position(float &x, float &y){
    uint16_t n;
    recv_short(n);
    x = (float)n/std::pow(10,DEC_SENT);

    recv_short(n);
    y = (float)n/std::pow(10,DEC_SENT);
}

void Protocol::send_event(const Event event){
    send_byte(event);
}

void Protocol::recv_event(Event &event){
    recv_byte((char &)event);
}

void Protocol::send_window_size(const uint16_t length, const uint16_t height){
    send_short(length);
    send_short(height);
}

void Protocol::recv_window_size(uint16_t &length, uint16_t &height){
    recv_short(length);
    recv_short(height);
}

void Protocol::send_pixel_position(const uint16_t x, const uint16_t y){
    send_short(x);
    send_short(y);
}

void Protocol::recv_pixel_position(uint16_t &x, uint16_t &y){
    recv_short(x);
    recv_short(y);
}