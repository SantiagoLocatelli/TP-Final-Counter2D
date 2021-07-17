#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>
enum SkinType : int {CT1, CT2, CT3, CT4, TT1, TT2, TT3, TT4};

enum WeaponType : char {KNIFE, PISTOL, SHOTGUN, RIFLE, SNIPER, BOMB, NO_WEAPON};

enum RoundState : char {BUY, MIDDLE, END};


enum WeaponSlot : uint8_t {KNIFE_SLOT = 0, SECONDARY = 1, PRIMARY = 2, BOMB_SLOT = 3};

enum Team : char {TERROR, COUNTER};

struct RectArea{
    float x;
    float y;
    float width;
    float height;
};

#endif