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

void Protocol::send_event(const Event event){
    send_byte(event);
}

void Protocol::recv_event(Event &event){
    recv_byte((char &)event);
}

void Protocol::send_float(const float &f){
    uint16_t n;
    n = std::floor(f*std::pow(10,DEC_SENT));
    send_short(n);
}

void Protocol::recv_float(float &f){
    uint16_t n;
    recv_short(n);
    f = (float)n/std::pow(10,DEC_SENT);
}

void Protocol::send_map_info(const MapInfo &mapInfo){
    send_short(mapInfo.height);
    send_short(mapInfo.length);

    //Envío el largo de la lista
    send_short(mapInfo.boxes.size());
    for (Box b: mapInfo.boxes){
        send_short(b.x);
        send_short(b.y);
    }
}

void Protocol::recv_map_info(MapInfo &mapInfo){
    recv_short(mapInfo.height);
    recv_short(mapInfo.length);

    //Envío el largo de la lista
    uint16_t len;
    recv_short(len);
    for (int i = 0; i < len; i++){
        Box b;
        recv_short(b.x);
        recv_short(b.y);
        mapInfo.boxes.push_back(b);
    }
}

void Protocol::send_model_info(const ModelInfo &modelInfo){
    send_float(modelInfo.you.x);
    send_float(modelInfo.you.y);
    send_float(modelInfo.you.angle);
    send_float(modelInfo.you.health);
    send_short(modelInfo.you.ammo);

    send_short(modelInfo.players.size());
    for (const Prot_Player &p: modelInfo.players){
        send_float(p.x);
        send_float(p.y);
        send_float(p.angle);
    }

    send_short(modelInfo.bullets.size());
    for (const Bullet &b: modelInfo.bullets){
        send_float(b.start_x);
        send_float(b.start_y);
        send_float(b.angle);
        send_float(b.distance);
    }

    char byte = 0;
    if (modelInfo.game_ended)
        byte = 1;
    send_byte(byte);
}

void Protocol::recv_model_info(ModelInfo &modelInfo){
    recv_float(modelInfo.you.x);
    recv_float(modelInfo.you.y);
    recv_float(modelInfo.you.angle);
    recv_float(modelInfo.you.health);
    recv_short(modelInfo.you.ammo);

    uint16_t len;
    recv_short(len);
    for (int i = 0; i < len; i++){
        Prot_Player p;
        recv_float(p.x);
        recv_float(p.y);
        recv_float(p.angle);
        modelInfo.players.push_back(p);
    }

    recv_short(len);
    for (int i = 0; i < len; i++){
        Bullet b;
        recv_float(b.start_x);
        recv_float(b.start_y);
        recv_float(b.angle);
        recv_float(b.distance);
        modelInfo.bullets.push_back(b);
    }

    char byte;
    recv_byte(byte);
    modelInfo.game_ended = byte == 1;
}

void Protocol::close(){
    skt.close_socket();
}
