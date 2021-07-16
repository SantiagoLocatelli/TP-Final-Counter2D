#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include "OptionsMenu.h"
#include "editor.h"
#include "GeneralException.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/draggable.h"
#include "MenuManager.h"
#include "InitialMenu.h"
#include "textureScreen.h"
#include "quitMenu.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]){
    try{
        SdlWindow window("Editor", 640, 480);
        SdlRenderer renderer(&window);

        MenuManager menuManager(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        std::stack<std::unique_ptr<Presenter>> presenter;
        
        presenter.emplace(std::unique_ptr<Presenter>(new Editor(renderer, menuManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
        presenter.emplace(std::unique_ptr<Presenter>(new InitialMenu(renderer, menuManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
        

        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event event;
        
        //While application is running
        while (!quit){
            //Handle events on queue
            while (SDL_PollEvent(&event) != 0){
                //User requests quit
                if (event.type == SDL_QUIT){
                    if (menuManager.getSaveState() != ""){
                        presenter.emplace(std::unique_ptr<Presenter>(new QuitMenu(quit, renderer, menuManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
                    }else{
                        quit = true;
                    }
                }
                presenter.top()->handleEvents(&event, renderer);
                if (presenter.top()->finish()){
                    if (presenter.size() > 1){
                        presenter.top()->aceptChanges();
                        presenter.pop();
                        if (menuManager.quitToMenu()){
                            presenter.emplace(std::unique_ptr<Presenter>(new InitialMenu(renderer, menuManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
                        }
                    }else if (event.key.keysym.sym == SDLK_ESCAPE){
                        presenter.emplace(std::unique_ptr<Presenter>(new OptionsMenu(renderer, menuManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
                    }else{
                        presenter.emplace(std::unique_ptr<Presenter>(new TextureScreen(renderer, menuManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
                    }
                }else if(event.key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_CTRL){
                    menuManager.loadToFile();
                }
                window.setTitle(presenter.top()->getTitle() + menuManager.getSaveState());
            }

            renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
            renderer.clear();

            presenter.top()->render();

            renderer.updateScreen();
        }
    }catch (const std::exception &e){
        std::cerr << "ERROR:" << e.what() << std::endl;
    }
    return 0;
}