#include "sdl_window.h"
#include <stdio.h>
#include <string>
#include <sstream>

SdlWindow::SdlWindow(std::string name, int width, int height){
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }else{
        this->mWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (this->mWindow == NULL){
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }else{
            this->mWidth = width;
            this->mHeight = height;
            this->mMouseFocus = true;
            this->mKeyboardFocus = true;
            this->mWindowID = SDL_GetWindowID(this->mWindow);
            this->mShown = true;
        }
    }
}

SDL_Renderer* SdlWindow::createRender(){
    this->mRenderer = SDL_CreateRenderer(this->mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return mRenderer;
}

int SdlWindow::getHeight(){
    return this->mHeight;
}

int SdlWindow::getWidth(){
    return this->mWidth;
}

SDL_Window* SdlWindow::getWindow(){
    return this->mWindow;
}


void SdlWindow::handleEvent(SDL_Event& e){
    if(e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID){
        switch(e.window.event){
            //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
            mShown = true;
            break;

            //Window disappeared
            case SDL_WINDOWEVENT_HIDDEN:
            mShown = false;
            break;

            //Get new dimensions and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            SDL_RenderPresent(this->mRenderer);
            break;

            //Repaint on expose
            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(this->mRenderer);
            break;

            //Mouse enter
            case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            break;
            
            //Mouse exit
            case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            break;

            //Keyboard focus gained
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            break;
            
            //Keyboard focus lost
            case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            break;

            //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

            //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;
            
            //Window restored
            case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
            
            //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow(this->mWindow);
            break;
        }
    }
}

void SdlWindow::focus(){
    //Restore window if needed
    if(!this->mShown){
        SDL_ShowWindow(this->mWindow);
    }

    //Move window forward
    SDL_RaiseWindow(this->mWindow);
}

void SdlWindow::render(){
    if(!this->mMinimized){    
        //Clear screen
        SDL_SetRenderDrawColor(this->mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(this->mRenderer);

        //Update screen
        SDL_RenderPresent(this->mRenderer);
    }
}

bool SdlWindow::hasMouseFocus(){
    return this->mMouseFocus;
}
bool SdlWindow::hasKeyboardFocus(){
    return this->mKeyboardFocus;
}
bool SdlWindow::isMinimized(){
    return this->mMinimized;
}
bool SdlWindow::isShown(){
    return this->mShown;
}

SdlWindow::~SdlWindow(){
    SDL_DestroyWindow(this->mWindow);
    SDL_Quit();
}
