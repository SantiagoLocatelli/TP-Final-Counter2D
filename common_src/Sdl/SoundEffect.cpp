#include "SoundEffect.h"
#include "../GeneralException.h"

SoundEffect::SoundEffect(std::string path) {
    this->effect = Mix_LoadWAV(path.c_str());
    if (this->effect == NULL) {
        throw GeneralException("No se pudo cargar el efecto de sonido: " + path);
    }
    this->effect->volume = 64;
}

SoundEffect::SoundEffect(){
    this->effect = NULL;
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

SoundEffect& SoundEffect::operator=(const SoundEffect& other){
    if (other.effect != NULL && other.effect != this->effect) {
        this->effect = other.effect;
        return *this;
    }
}


SoundEffect::~SoundEffect(){
    if (this->effect != NULL) {
        Mix_FreeChunk(this->effect);
        this->effect = NULL;
    }
}

void SoundEffect::play(int repeat){
    Mix_PlayChannel(-1, this->effect, repeat);
}

void SoundEffect::playTimed(int repeat, int ticks) {
    Mix_PlayChannelTimed(-1, this->effect, repeat, ticks);
}

void SoundEffect::setearVolume(int volume){
    // el maximo es 128 (SDL), lo mapeo a procentaje
    this->effect->volume = volume*128/100;
}