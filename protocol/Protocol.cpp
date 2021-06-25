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

void Protocol::send_float(const float &num){
    uint16_t n;
    n = std::floor(num*std::pow(10,DEC_SENT));
    send_short(n);
}

void Protocol::recv_float(float &num){
    uint16_t n;
    recv_short(n);
    num = (float)n/std::pow(10,DEC_SENT);
}

void Protocol::send_event(const Event event){
    send_byte(event);
}

void Protocol::recv_event(Event &event){
    recv_byte((char &)event);
}

void Protocol::send_map_info(const MapInfo &mapInfo){
    //Envío el tamaño
    send_short(mapInfo.height);
    send_short(mapInfo.length);

    //Envío la cantidad de cajas
    send_short(mapInfo.boxes.size());
    
    //Envío las cajas
    for (Box b: mapInfo.boxes){
        send_short(b.x);
        send_short(b.y);
    }
}

void Protocol::recv_map_info(MapInfo &mapInfo){
    //Recibo el tamaño
    recv_short(mapInfo.height);
    recv_short(mapInfo.length);

    //Recibo la cantidad de cajas
    uint16_t size;
    recv_short(size);
    
    //Envío las cajas
    for (int i = 0; i < size; i++){
        Box b;
        recv_short(b.x);
        recv_short(b.y);
        mapInfo.boxes.push_back(b);
    }
}

void Protocol::send_model_info(const ModelInfo &modelInfo){
    //Envío al You
    send_float(modelInfo.you.x);
    send_float(modelInfo.you.y);
    send_float(modelInfo.you.angle);
    send_float(modelInfo.you.health);
    send_short(modelInfo.you.ammo);

    //Envío a los jugadores
    send_short(modelInfo.players.size());
    for (Player p : modelInfo.players){
        send_float(p.x);
        send_float(p.y);
        send_float(p.angle);
    }

    //Envío a los disparos
    send_short(modelInfo.bullets.size());
    for (Bullet b : modelInfo.bullets){
        send_float(b.start_x);
        send_float(b.start_y);
        send_float(b.angle);
    }
}

void Protocol::recv_model_info(ModelInfo &modelInfo){
    //Envío al You
    recv_float(modelInfo.you.x);
    recv_float(modelInfo.you.y);
    recv_float(modelInfo.you.angle);
    recv_float(modelInfo.you.health);
    recv_short(modelInfo.you.ammo);

    //Envío a los jugadores
    uint16_t size;
    recv_short(size);
    for (int i = 0; i < size; i++){
        Player p;
        recv_float(p.x);
        recv_float(p.y);
        recv_float(p.angle);
        modelInfo.players.push_back(p);
    }

    //Envío a los disparos
    recv_short(size);
    for (int i = 0; i < size; i++){
        Bullet b;
        send_float(b.start_x);
        send_float(b.start_y);
        send_float(b.angle);
        modelInfo.bullets.push_back(b);
    }
}
