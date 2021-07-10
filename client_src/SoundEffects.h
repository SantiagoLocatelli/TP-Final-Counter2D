#ifndef __SOUND_EFFECTS_H__
#define __SOUND_EFFECTS_H__

#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL.h"
#include <map>

enum PlayerEffect : int {STEP, DYING, DROPPING, PICKING_UP};
enum WeaponEffect : int {KNIFE_SLASH, KNIFE_HIT, SHOT_PISTOL, SHOT_RIFLE, SHOT_SHOTGUN, SHOT_SNIPER, 
    BOMD_EXPLODE, BOMB_DEFUSE, BOMB_PIP};

class SoundEffects {
private:

    std::map<PlayerEffect, Mix_Chunk*> playerEffects;
    std::map<WeaponEffect, Mix_Chunk*> weaponsEffects;

    void loadPlayerSounds();
    void loadWeaponSounds();

public:

    SoundEffects();
    ~SoundEffects();

    void playWeaponSound(WeaponEffect effect);
    void playPlayerSound(PlayerEffect effect);
};

#endif