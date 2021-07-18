#include "LoadingMenu.h"
#include "../common_src/GeneralException.h"
#include "../common_src/Stopwatch.h"
#include <string>
#include <map>
#include "SDL2/SDL.h"

#define PATH_FONT_DIGITAL "../../common_src/img/digital-7.ttf"
#define WINDOW_LABEL " "

#define VIEJA_PATH_TEXTURE "../../common_src/img/vieja.png"
#define VIEJA_PATH_SOUND "../../common_src/sound/vieja.wav"
#define BACKGROUND_PATH "../../common_src/img/counter.jpeg"
#define FONT_SIZE 30
#define MARGIN 20

const struct Color WHITE = {0xff, 0xff, 0xff};

LoadingMenu::LoadingMenu(Size windowSize):window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), loading(true), background(renderer, BACKGROUND_PATH),
    oldLady(renderer, VIEJA_PATH_TEXTURE, WHITE.r, WHITE.g, WHITE.b),
    textLoading(renderer, PATH_FONT_DIGITAL, FONT_SIZE){

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        char err[200];
        sprintf(err, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        throw GeneralException(err);
    }
    this->shot = Mix_LoadWAV(VIEJA_PATH_SOUND);
    Mix_VolumeChunk(this->shot, 64);
}

void LoadingMenu::run() {

    int framesLoading = 4;
    int actualFrame = 0;
    std::map<int, std::string> loadingTexts;
    loadingTexts[0] = "Waiting for players";
    loadingTexts[1] = "Waiting for players.";
    loadingTexts[2] = "Waiting for players..";
    loadingTexts[3] = "Waiting for players...";

    Size windowSize = {this->window.getWidth(), this->window.getHeight()};
    Coordinate posLoading = {windowSize.w/2, 3*windowSize.h/4};
    
    Size sizeLady = {windowSize.w/3, windowSize.h/3};
    Coordinate posLady = {windowSize.w/2 - sizeLady.w/2, windowSize.h/2 - sizeLady.h/2};
    
    TextTexture muteText(this->renderer, PATH_FONT_DIGITAL, 15);
    muteText.setText("Press m to mute or unmute", WHITE);
    Size muteSize = muteText.getSize();
    Coordinate mutePos = {MARGIN, windowSize.h - MARGIN - muteSize.h};
    muteText.setCoordinate(mutePos);

    // SDL_FLIP_HORIZONTAL = 1
    // SDL_FLIP_NONE = 0
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    Stopwatch stopwatch;
    stopwatch.start();
    SDL_Event e;
    bool mute = false;
    while (loading) {
        SDL_PollEvent(&e);
        if (e.type == SDL_MOUSEMOTION) {
            continue;
        } else if (e.type == SDL_QUIT) {
            loading = false;
        } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 &&  e.key.keysym.sym == SDLK_m) {
            mute = !mute;
        }

        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        this->background.render(0, 0, windowSize.w, windowSize.h);

        this->textLoading.setText(loadingTexts[actualFrame], WHITE);
        Size textSize = this->textLoading.getSize();
        this->textLoading.render({posLoading.x - textSize.w/2, posLoading.y});

        if (stopwatch.msPassed() > FRAME_MS*30) {
            stopwatch.start();
            
            if (!mute) Mix_PlayChannel(-1, this->shot, 0);
            
            if (flip == SDL_FLIP_NONE) {
                flip = SDL_FLIP_HORIZONTAL;
            } else {
                flip = SDL_FLIP_NONE;
            }
            actualFrame++;
            actualFrame = actualFrame % framesLoading;
        }

        this->oldLady.render(posLady.x, posLady.y, sizeLady.w, sizeLady.h, NULL, 0.0, NULL, flip);
        muteText.render();


        renderer.updateScreen();
    }
}

void LoadingMenu::close(){
    this->loading = false;
}

LoadingMenu::~LoadingMenu(){
    if (this->shot != NULL) {
        Mix_FreeChunk(this->shot);
        this->shot = NULL;
    }
}