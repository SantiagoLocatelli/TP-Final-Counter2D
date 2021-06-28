#include <SDL2/SDL.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_window.h"
#include "../Sdl/sdl_renderer.h"
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

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //Level camera
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //While application is running
    while (!quit){
        //Handle events on queue
        while (SDL_PollEvent(&event) != 0){
            //User requests quit
            if (event.type == SDL_QUIT){
                quit = true;
            }else if (event.type == SDL_MOUSEBUTTONDOWN){
                //On left mouse click
                if (event.button.button == SDL_BUTTON_LEFT){
                    editor.put_tile(camera, renderer);
                }
            }else{
                editor.handleEvents(&event);
                window.setTitle("Level Designer. Current Tile: " + editor.getTitle());
            }
        }

        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();


        setCamera(camera);

        int x = 0, y = 0;

        editor.render(camera);

        renderer.updateScreen();
    }
    editor.saveMap();
    return 0;
}

void setCamera(SDL_Rect& camera)
{
	//Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState( &x, &y );
    
    //Move camera to the left if needed
    if( x < TILE_WIDTH )
    {
        camera.x -= 20;
    }
    
    //Move camera to the right if needed
    if( x > SCREEN_WIDTH - TILE_WIDTH )
    {
        camera.x += 20;
    }
    
    //Move camera up if needed
    if( y < TILE_WIDTH )
    {
        camera.y -= 20;
    }
    
    //Move camera down if needed
    if( y > SCREEN_HEIGHT - TILE_WIDTH )
    {
        camera.y += 20;
    }

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}