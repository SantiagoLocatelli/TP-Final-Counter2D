#include "Protocol.h"
#include <arpa/inet.h>
#include <utility>
#include <cmath>

Protocol::Protocol(Socket skt):skt(std::move(skt)){}

Protocol::Protocol(Protocol&& other):skt(std::move(other.skt)){} 

void Protocol::send_uint16t(const uint16_t &buf){
    uint16_t ns = htons(buf);
    skt.send_buffer((char *)&ns, 2);
}

void Protocol::recv_uint16t(uint16_t &buf){
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

void Protocol::send_bool(const bool &b){
    char byte = b ? 1 : 0;
    send_byte(byte);
}

void Protocol::recv_bool(bool &b){
    char byte;
    recv_byte(byte);

    b = byte == 1;
}


void Protocol::send_event(const Event event){
    send_byte(event.type);
    skt.send_buffer((char *)&(event.info), sizeof(event.info));
}

void Protocol::recv_event(Event &event){
    recv_byte((char &)event.type);
    skt.recv_buffer((char *)&(event.info), sizeof(event.info));
}

void Protocol::send_float(const float &f){
    uint16_t n;
    n = std::floor(f*std::pow(10,DEC_SENT));
    send_uint16t(n);
}

void Protocol::recv_float(float &f){
    uint16_t n;
    recv_uint16t(n);
    f = (float)n/std::pow(10,DEC_SENT);
}

void Protocol::send_map_info(const MapInfo &mapInfo){
    send_uint16t(mapInfo.height);
    send_uint16t(mapInfo.length);

    for (int i = 0; i < mapInfo.height*mapInfo.length; i++){
        send_byte(mapInfo.tiles[i]);
    }

    send_uint16t(mapInfo.bombSites.size());
    for (const RectArea &r: mapInfo.bombSites){
        send_float(r.x);
        send_float(r.y);
        send_float(r.height);
        send_float(r.width);
    }

    send_uint16t(mapInfo.spawnSites.size());
    for (const RectArea &r: mapInfo.spawnSites){
        send_float(r.x);
        send_float(r.y);
        send_float(r.height);
        send_float(r.width);
    }
}

void Protocol::recv_map_info(MapInfo &mapInfo){
    recv_uint16t(mapInfo.height);
    recv_uint16t(mapInfo.length);

    for (int i = 0; i < mapInfo.height*mapInfo.length; i++){
        uint8_t tile;
        recv_byte((char &)tile);
        mapInfo.tiles.push_back(tile);
    }

    uint16_t len;
    recv_uint16t(len);
    mapInfo.bombSites.clear();
    for (int i = 0; i < len; i++){
        RectArea r;
        recv_float(r.x);
        recv_float(r.y);
        recv_float(r.height);
        recv_float(r.width);
        mapInfo.bombSites.push_back(r);
    }

    recv_uint16t(len);
    mapInfo.spawnSites.clear();
    for (int i = 0; i < len; i++){
        RectArea r;
        recv_float(r.x);
        recv_float(r.y);
        recv_float(r.height);
        recv_float(r.width);
        mapInfo.spawnSites.push_back(r);
    }
}

void Protocol::send_model_info(const ModelInfo &modelInfo){
    send_bool(modelInfo.you.dead);
    if (!modelInfo.you.dead){
        send_float(modelInfo.you.pos.x);
        send_float(modelInfo.you.pos.y);
        send_float(modelInfo.you.angle);
        send_byte(modelInfo.you.weapon);
        send_bool(modelInfo.you.shot);
        send_float(modelInfo.you.health);
        send_uint16t(modelInfo.you.ammo);
        send_byte(modelInfo.you.team);
    }


    send_uint16t(modelInfo.players.size());
    for (const ProtPlayer &p: modelInfo.players){
        send_bool(p.dead);
        if (!p.dead){
            send_float(p.pos.x);
            send_float(p.pos.y);
            send_float(p.angle);
            send_byte(p.weapon);
            send_bool(p.shot);
            send_byte(modelInfo.you.team);
        }
    }

    send_uint16t(modelInfo.bullets.size());
    for (const Bullet &b: modelInfo.bullets){
        send_float(b.pos.x);
        send_float(b.pos.y);
        send_float(b.angle);
        send_float(b.distance);
    }

    send_uint16t(modelInfo.drops.size());
    for (const ProtDrop &d: modelInfo.drops){
        send_byte(d.type);
        send_float(d.pos.x);
        send_float(d.pos.y);
    }

    send_bool(modelInfo.game_ended);

    send_bool(modelInfo.bomb.planted);
    if (modelInfo.bomb.planted){
        send_bool(modelInfo.bomb.defused);
        send_float(modelInfo.bomb.x);
        send_float(modelInfo.bomb.y);
        send_float(modelInfo.bomb.timeRemaining);
    }
}

void Protocol::recv_model_info(ModelInfo &modelInfo){
    recv_bool(modelInfo.you.dead);
    if (!modelInfo.you.dead){
        recv_float(modelInfo.you.pos.x);
        recv_float(modelInfo.you.pos.y);
        recv_float(modelInfo.you.angle);
        recv_byte((char&)modelInfo.you.weapon);
        recv_bool(modelInfo.you.shot);
        recv_float(modelInfo.you.health);
        recv_uint16t(modelInfo.you.ammo);
        recv_byte((char&)modelInfo.you.team);
    }

    uint16_t len;
    recv_uint16t(len);
    modelInfo.players.clear();
    for (int i = 0; i < len; i++){
        ProtPlayer p;
        recv_bool(p.dead);
        if (!p.dead){
            recv_float(p.pos.x);
            recv_float(p.pos.y);
            recv_float(p.angle);
            recv_byte((char&)p.weapon);
            recv_bool(p.shot);
            recv_byte((char&)modelInfo.you.team);
        }
        modelInfo.players.push_back(p);
    }

    recv_uint16t(len);
    modelInfo.bullets.clear();
    for (int i = 0; i < len; i++){
        Bullet b;
        recv_float(b.pos.x);
        recv_float(b.pos.y);
        recv_float(b.angle);
        recv_float(b.distance);
        modelInfo.bullets.push_back(b);
    }

    recv_uint16t(len);
    modelInfo.drops.clear();
    for (int i = 0; i < len; i++){
        ProtDrop d;
        recv_byte((char&)d.type);
        recv_float(d.pos.x);
        recv_float(d.pos.y);
        modelInfo.drops.push_back(d);
    }
    
    recv_bool(modelInfo.game_ended);

    recv_bool(modelInfo.bomb.planted);
    if (modelInfo.bomb.planted){
        recv_bool(modelInfo.bomb.defused);
        recv_float(modelInfo.bomb.x);
        recv_float(modelInfo.bomb.y);
        recv_float(modelInfo.bomb.timeRemaining);
    }
}

void Protocol::close(){
    skt.close_socket();
}

void Protocol::send_game_list(const std::list<GameInfo> &gameList){
    send_uint16t(gameList.size());
    for (const GameInfo &game : gameList){
        skt.send_buffer(game.name, 30);
        skt.send_buffer(game.map, 30);
        send_uint16t(game.players);
        send_uint16t(game.max_players);
    }
}

void Protocol::recv_game_list(std::list<GameInfo> &gameList){
        uint16_t len;
        recv_uint16t(len);
        gameList.clear();
    for (int i = 0; i < len; i++){
        GameInfo game;
        skt.recv_buffer(game.name, 30);
        skt.recv_buffer(game.map, 30);
        recv_uint16t(game.players);
        recv_uint16t(game.max_players);
        gameList.push_back(game);
    } 
}
