#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {
private:
    Mix_Chunk* effect;

public:

    SoundEffect(std::string path);

    SoundEffect(SoundEffect&&);
    SoundEffect operator=(SoundEffect&&);
};

#endif