#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_

#include <list>
#include <array>
#include <stdint.h>
#include "Utils.h"

#define FRAME_MS 33


struct Position{
    float x;
    float y;
};

struct ProtPlayer{
    bool dead; //Si es verdadero entonces todos los otros campos son inválidos
    Position pos;
    float angle; //En radianes
    std::array<WeaponType, 4> weapons;
    WeaponSlot currentSlot;
    bool shot;
    Team team;
};

struct You: public ProtPlayer{
    float health;
    uint16_t ammo;
    uint16_t money;
};

struct Bullet{
    Position pos;
    float angle; //En radianes
    float distance;
};

struct ProtDrop{
    WeaponType type;
    Position pos;
};

struct ProtState{
    RoundState roundState;
    
    //Cuando roundState == END te dice el estado de la partida en general. 
    //Si siguen jugando, si alguien ganó o empataron.
    GameState gameState; 

    //Si roundState == END te dice porque termino la ronda.
    RoundResult endResult;
    std::array<uint8_t, 2> roundScore; //Las rondas ganadas de cada equipo
};

struct ProtBomb{
    bool planted; //Si es falso entonces todos los otros campos son inválidos
    bool defused;
    float x;
    float y;
    float timeRemaining;
};

struct ModelInfo{
    You you;
    std::list<ProtPlayer> players;
    std::list<Bullet> bullets;
    std::list<ProtDrop> drops;
    ProtBomb bomb;
    bool game_ended;
    ProtState state;
    float timeRemaining;
};

#endif
