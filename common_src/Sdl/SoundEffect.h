#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {
private:
    Mix_Chunk* effect;

public:

    SoundEffect();
    SoundEffect(std::string path);
    ~SoundEffect();

    void play(int repeat);
    void playTimed(int repeat, int ticks);
    
    // en porcentaje
    void setearVolume(int volume);

    SoundEffect(SoundEffect&&);
    SoundEffect& operator=(SoundEffect&&);
    SoundEffect& operator=(const SoundEffect&);
};

#endif