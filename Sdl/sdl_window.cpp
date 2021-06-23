#include "sdl_window.h"
#include <stdio.h>
#include <string>

SdlWindow::SdlWindow(std::string name, int width, int height){
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }else{
        this->mWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (this->mWindow == NULL){
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }else{
            this->mWidth = width;
            this->mHeight = height;
        }
    }
}

SDL_Renderer* SdlWindow::createRender(){
    return SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

int SdlWindow::getHeight(){
    return this->mHeight;
}

int SdlWindow::getWidth(){
    return this->mWidth;
}

SdlWindow::~SdlWindow(){
    SDL_DestroyWindow(this->mWindow);
    SDL_Quit();
}
