#ifndef __SDL_MIXER_H__
#define __SDL_MIXER_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
class SdlMixer{
    private:
        Mix_Music* mMusic;
        std::vector<Mix_Chunk*> mChunks;
    public:
        SdlMixer(std::string musicPath);
        SdlMixer(std::string musicPath, std::vector<std::string>& chunkPaths);
        void play();
        void stop();
        void pause();
        void playChunk(int specificChunk);
        ~SdlMixer();
};
#endif
