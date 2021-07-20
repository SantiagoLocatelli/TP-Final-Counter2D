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
#include "InitialMenu.h"
#include "textureScreen.h"
#include "quitMenu.h"

int main(int argc, char* args[]){
    try{
        SdlWindow window("Editor", EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT);
        SdlRenderer renderer(&window);
        //window.setFullScreen();

        MenuManager menuManager(renderer, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT);

        std::stack<std::unique_ptr<Presenter>> presenter;
        
        presenter.emplace(std::unique_ptr<Presenter>(new Editor(renderer, menuManager, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT)));
        presenter.emplace(std::unique_ptr<Presenter>(new InitialMenu(renderer, menuManager, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT)));

        //Main loop flag
        bool quit = false, music = true;

        //Event handler
        SDL_Event event;
        
        menuManager.playMusic();
        Mix_VolumeMusic(64);
        //While application is running
        while (!quit){
            //Handle events on queue
            while (SDL_PollEvent(&event) != 0){
                //User requests quit
                if (menuManager.quit() || event.type == SDL_QUIT){
                    if (menuManager.getSaveState() != ""){
                        presenter.emplace(std::unique_ptr<Presenter>(new QuitMenu(quit, renderer, menuManager, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT)));
                    }else{
                        quit = true;
                    }
                }else if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_9){
                        if (music){
                            menuManager.pauseMusic();
                            music = false;
                        }else{
                            menuManager.playMusic();
                            music = true;
                        }
                    }
                }
                presenter.top()->handleEvents(&event, renderer);
                if (presenter.top()->finish()){
                    if (presenter.size() > 1){
                        presenter.top()->aceptChanges();
                        presenter.pop();
                        if (menuManager.quitToMenu()){
                            presenter.emplace(std::unique_ptr<Presenter>(new InitialMenu(renderer, menuManager, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT)));
                        }
                    }else if (event.key.keysym.sym == SDLK_ESCAPE){
                        presenter.emplace(std::unique_ptr<Presenter>(new OptionsMenu(renderer, menuManager, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT)));
                    }else{
                        presenter.emplace(std::unique_ptr<Presenter>(new TextureScreen(renderer, menuManager, EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT)));
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