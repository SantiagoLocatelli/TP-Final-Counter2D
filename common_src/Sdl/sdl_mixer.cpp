#include "sdl_mixer.h"
#include <stdio.h>
#include <string>
#include <vector>

SdlMixer::SdlMixer(std::string musicPath){
    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }else{
        this->mMusic = Mix_LoadMUS(musicPath.c_str());
	    if(this->mMusic == NULL){
		    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	    }
    }
}

SdlMixer::SdlMixer(std::string musicPath, std::vector<std::string>& chunkPaths){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }else{
        this->mMusic = Mix_LoadMUS(musicPath.c_str());
	    if (this->mMusic == NULL){
		    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	    }
        for (auto chunk : chunkPaths){
            this->mChunks.push_back(Mix_LoadWAV(chunk.c_str()));
            if (this->mChunks.back() == NULL){
                printf("Failed to load chunk: %s sound effect! number: SDL_mixer Error: %s\n", chunk, Mix_GetError());
            }
        }
    }
}

void SdlMixer::play(){
    if (Mix_PlayingMusic() == 0){
        //play the music
        Mix_PlayMusic(this->mMusic, -1);
    }
    if(Mix_PausedMusic() == 1){
        //Resume the music
        Mix_ResumeMusic();
    }
}

void SdlMixer::pause(){
    Mix_PauseMusic();
}

void SdlMixer::stop(){
    Mix_HaltMusic();
}

void SdlMixer::playChunk(int specificChunk){
    Mix_PlayChannel(-1, this->mChunks[specificChunk], 0);
}

SdlMixer::~SdlMixer(){
    Mix_FreeMusic(this->mMusic);
    for(auto chunk : this->mChunks){
        Mix_FreeChunk(chunk);
    }
    Mix_Quit();
	delete this->mMusic;
}
