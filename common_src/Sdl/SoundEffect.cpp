#include "SoundEffect.h"

SoundEffect::SoundEffect(std::string path) {
    this->effect = Mix_LoadWAV(path.c_str());
}

SoundEffect::SoundEffect(SoundEffect&& other){
    if (other.effect != NULL && other.effect != this->effect) {
        this->effect = other.effect;
        other.effect = NULL;
    }
}

SoundEffect& SoundEffect::operator=(SoundEffect&& other){
    if (other.effect != NULL && other.effect != this->effect) {
        this->effect = other.effect;
        other.effect = NULL;
        return *this;
    }
}

SoundEffect::~SoundEffect(){
    Mix_FreeChunk(this->effect);
}

void SoundEffect::play(int repeat){
    Mix_PlayChannel(-1, this->effect, repeat);
}

void SoundEffect::playTimed(int repeat, int ticks) {
    Mix_PlayChannelTimed(-1, this->effect, repeat, ticks);
}

void SoundEffect::setearVolume(int volume){
    Mix_VolumeChunk(this->effect, volume);
}