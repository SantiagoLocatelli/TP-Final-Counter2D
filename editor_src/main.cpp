#include <SDL2/SDL.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_window.h"
#include "../Sdl/sdl_renderer.h"
#include "../Character/camera.h"
#include "../Sdl/draggable.h"
#include "editor.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;


//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

void setCamera(SDL_Rect& camera);

int main(int argc, char* args[]){

    SdlWindow window("Editor", 640, 480);
    SdlRenderer renderer(&window);
	
    Editor editor("../common_src/maps/map.yaml", renderer);

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    Draggable* bombSiteA = NULL;
    Draggable* bombSiteB = NULL;
    std::vector<SDL_Rect> bombSites = editor.getBombSite();

    Draggable* spawnSiteT = NULL;
    Draggable* spawnSiteCT = NULL;
    std::vector<SDL_Rect> spawnSites = editor.getSpawnSite();
    

    //While application is running
    while (!quit){
        //Handle events on queue
        camera.centerCameraOnMouse(TILE_WIDTH, LEVEL_WIDTH, LEVEL_HEIGHT);
        while (SDL_PollEvent(&event) != 0){
            //User requests quit
            if (event.type == SDL_QUIT){
                quit = true;
            }else if (event.type == SDL_MOUSEBUTTONDOWN){
                //On left mouse click
                if (event.button.button == SDL_BUTTON_RIGHT){
                    editor.put_tile(camera.getRect(), renderer);
                }
            }else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_1){
                    if (bombSiteA == NULL && bombSiteB == NULL){
                        bombSiteA = new Draggable(renderer, "../common_src/img/bombSite.png", bombSites[0].x, bombSites[0].y , 255,0,0);
                        bombSiteA->setBlendMode(SDL_BLENDMODE_BLEND);
                        bombSiteB = new Draggable(renderer, "../common_src/img/bombSite.png", bombSites[1].x, bombSites[1].y , 255,0,0);
                        bombSiteB->setBlendMode(SDL_BLENDMODE_BLEND);
                    }
                }else if (event.key.keysym.sym == SDLK_2){
                    if (spawnSiteT == NULL && spawnSiteCT == NULL){
                        spawnSiteT = new Draggable(renderer, "../common_src/img/spawnSite.png", spawnSites[0].x, spawnSites[0].y , 255,0,0);
                        spawnSiteT->setBlendMode(SDL_BLENDMODE_BLEND);
                        spawnSiteCT = new Draggable(renderer, "../common_src/img/spawnSite.png", spawnSites[1].x, spawnSites[1].y , 255,0,0);
                        spawnSiteCT->setBlendMode(SDL_BLENDMODE_BLEND);
                    }
                }
            }else if (event.type == SDL_KEYUP){
                if (event.key.keysym.sym == SDLK_1){
                    delete bombSiteA;
                    bombSiteA = NULL;
                    delete bombSiteB;
                    bombSiteB = NULL;
                }else if (event.key.keysym.sym == SDLK_2){
                    delete spawnSiteT;
                    spawnSiteT = NULL;
                    delete spawnSiteCT;
                    spawnSiteCT = NULL;
                }
            }
            else{
                editor.handleEvents(&event);
                window.setTitle("Level Designer. Current Tile: " + editor.getTitle());
            }
            if (bombSiteA != NULL && bombSiteB != NULL){
                bombSiteA->handleEvent(&event, camera.getRect());
                bombSiteB->handleEvent(&event, camera.getRect());
            }
            if (spawnSiteT != NULL && spawnSiteCT != NULL){
                spawnSiteT->handleEvent(&event, camera.getRect());
                spawnSiteCT->handleEvent(&event, camera.getRect());
            }
        }

        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();
        camera.centerCameraOnMouse(TILE_WIDTH, LEVEL_WIDTH, LEVEL_HEIGHT);

        editor.render(camera.getRect());

        if (bombSiteA != NULL && bombSiteB != NULL){
            bombSiteA->setAlpha(100);
            bombSiteA->render(camera.getRect(), bombSites[0].w, bombSites[0].h);
            bombSiteB->setAlpha(100);
            bombSiteB->render(camera.getRect(), bombSites[1].w, bombSites[1].h);
            bombSites[0].x = bombSiteA->getPosX();
            bombSites[0].y = bombSiteA->getPosY();
            bombSites[1].x = bombSiteB->getPosX();
            bombSites[1].y = bombSiteB->getPosY();
        }

        if (spawnSiteT != NULL && spawnSiteCT != NULL){
            spawnSiteT->setAlpha(100);
            spawnSiteT->render(camera.getRect(), spawnSites[0].w, spawnSites[0].h);
            spawnSiteCT->setAlpha(100);
            spawnSiteCT->render(camera.getRect(), spawnSites[1].w, spawnSites[1].h);
            spawnSites[0].x = spawnSiteT->getPosX();
            spawnSites[0].y = spawnSiteT->getPosY();
            spawnSites[1].x = spawnSiteCT->getPosX();
            spawnSites[1].y = spawnSiteCT->getPosY();
        }

        renderer.updateScreen();
    }
    editor.setBombSite(bombSites);
    editor.setSpawnSite(spawnSites);
    editor.saveMap();
    return 0;
}