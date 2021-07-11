#include "SoundEffects.h"
#include "../common_src/GeneralException.h"
#include "yaml-cpp/yaml.h"
#include <string>

SoundEffects::SoundEffects(){
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        char err[200];
        sprintf(err, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        throw GeneralException(err);
    }
    Mix_Volume(-1, 64);
    loadPlayerSounds();
    loadWeaponSounds();
}

void SoundEffects::loadPlayerSounds(){
    YAML::Node yaml_map = YAML::LoadFile("../../client_src/yaml/playerSounds.yaml");
	int i = 0;
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> sound = it->as<std::pair<std::string, int>>();
        PlayerEffect effect = (PlayerEffect)sound.second;
        this->playerEffects[effect] = Mix_LoadWAV(sound.first.c_str());
        Mix_VolumeChunk(this->playerEffects[effect], 64);
        i++;
    }
}


void SoundEffects::loadWeaponSounds(){
    YAML::Node yaml_map = YAML::LoadFile("../../client_src/yaml/weaponsSounds.yaml");
	int i = 0;
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> sound = it->as<std::pair<std::string, int>>();
        WeaponEffect effect = (WeaponEffect)sound.second;
        this->weaponsEffects[effect] = Mix_LoadWAV(sound.first.c_str());
        Mix_VolumeChunk(this->weaponsEffects[effect], 64);
        i++;
    }
}


void SoundEffects::playPlayerSound(PlayerEffect effect){
    Mix_PlayChannel(-1, this->playerEffects[effect], 1);
}

void SoundEffects::playWeaponSound(WeaponEffect effect){
    Mix_PlayChannel(-1, this->weaponsEffects[effect], 1);
}


SoundEffects::~SoundEffects(){
    for(auto it = this->playerEffects.begin(); it != this->playerEffects.end(); it++){
        Mix_FreeChunk(it->second);
    }
    for(auto it = this->weaponsEffects.begin(); it != this->weaponsEffects.end(); it++){
        Mix_FreeChunk(it->second);
    }
    Mix_Quit();
}

