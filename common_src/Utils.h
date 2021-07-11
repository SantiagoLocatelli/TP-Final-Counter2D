#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>

enum WeaponType : char {KNIFE, PISTOL, SHOTGUN, RIFLE, SNIPER, BOMB};

enum WeaponSlot : uint8_t {KNIFE_SLOT = 0, SECONDARY = 1, PRIMARY = 2, BOMB_SLOT = 3};

enum Team : char {TERROR, COUNTER};

struct RectArea{
    float x;
    float y;
    float width;
    float height;
};

#endif