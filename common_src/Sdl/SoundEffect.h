#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {
private:
    Mix_Chunk* effect;

public:

    SoundEffect(std::string path);
    ~SoundEffect();

    void play(int repeat);
    void playTimed(int repeat, int ticks);
    // va de 0 a 128
    void setearVolume(int volume);

    SoundEffect(SoundEffect&&);
    SoundEffect& operator=(SoundEffect&&);
};

#endif