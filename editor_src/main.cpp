#include <SDL2/SDL.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include "OptionsMenue.h"
#include "editor.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/draggable.h"
#include "MenueManager.h"
#include "InitialMenue.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main(int argc, char* args[]){

    SdlWindow window("Editor", 640, 480);
    SdlRenderer renderer(&window);

    MenueManager menueManager(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    std::stack<std::unique_ptr<Presenter>> presenter;
    
    presenter.emplace(std::unique_ptr<Presenter>(new Editor(menueManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
    presenter.emplace(std::unique_ptr<Presenter>(new InitialMenue(renderer, menueManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
    

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
                quit = true;
            }else if (presenter.top()->finish()){
                if (presenter.size() > 1){
                    presenter.top()->aceptChanges();
                    presenter.pop();
                }else{
                    presenter.emplace(std::unique_ptr<Presenter>(new OptionsMenue(renderer, menueManager, SCREEN_WIDTH, SCREEN_HEIGHT)));
                }
            }
            presenter.top()->handleEvents(&event, renderer);
            window.setTitle("Level Designer. Current Tile: " + presenter.top()->getTitle());
        }

        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        presenter.top()->render();

        renderer.updateScreen();
    }
    menueManager.loadToFile();
    return 0;
}