#include <SDL2/SDL.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_window.h"
#include "../Sdl/sdl_renderer.h"
#include "../Sdl/draggable.h"
#include "../Sdl/game_object.h"
#include "../Sdl/floor.h"
#include "../Sdl/wall.h"

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

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

void setClips(std::vector<SDL_Rect>& clips);
void put_tile( std::vector<GameObject*>& objects, int objectType, SDL_Rect& camera, std::vector<SDL_Rect>& clip, SdlRenderer& renderer, std::string path);
bool setObjects( std::vector<GameObject*>& objects, SdlRenderer& renderer, std::string path, std::vector<SDL_Rect>& clips);
void show_type(SDL_Window* gWindow, int tileType );
void setCamera( SDL_Rect& camera );
void close( std::vector<GameObject*>& objects );

int main( int argc, char* args[] )
{
	std::vector<SDL_Rect> clips;
	setClips(clips);
    SdlWindow window("Editor", 640, 480);
    SdlRenderer renderer(&window);
	//The frame rate regulator
	//Timer fps;
	
	//The level objects
	std::vector<GameObject*> objects;

	//Load media
	std::string path("tiles.png");
	if( !setObjects( objects, renderer, path, clips ) )
	{
		printf( "Failed to load media!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event event;

		//Current tile type
		int currentType = TILE_RED;

		//Level camera
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		//While application is running
		while( !quit )
		{
			//Start the frame timer
			//fps.start();

			//Handle events on queue
			while( SDL_PollEvent( &event ) != 0 )
			{
				//User requests quit
				if( event.type == SDL_QUIT )
				{
					quit = true;
				}

				else if ( event.type == SDL_MOUSEBUTTONDOWN ){
					//On left mouse click
					if( event.button.button == SDL_BUTTON_LEFT ){
						//Put the tile
						put_tile( objects, currentType, camera, clips, renderer, path );
					}
				}
				else if (event.type == SDL_MOUSEWHEEL){
					//On mouse wheel scroll
					if( event.wheel.y > 0)
					{
						//Scroll through tiles
						currentType--;
						
						if( currentType < TILE_RED )
						{
							currentType = TILE_TOPLEFT;
						}
						
						//Show the current tile type
						show_type( window.getWindow(), currentType );
					}
					else if(event.wheel.y < 0)
					{
						//Scroll through tiles
						currentType++;
						
						if( currentType > TILE_TOPLEFT )
						{
							currentType = TILE_RED;
						}
						
						//Show the current tile type
						show_type( window.getWindow(), currentType );
					}
				}
			}

			renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
			renderer.clear();


			setCamera(camera);
			//Render level
			/*for( int i = 0; i < TOTAL_TILES; ++i )
			{
				objects[ i ]->render( camera );
			}*/

			for (auto object : objects){
				object->render(camera);
			}

			renderer.updateScreen();
			//Cap the frame rate
			/*if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
				SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
			}*/
			
		}
	}
	//Free resources and close SDL
	close( objects );

return 0;
}

void setClips(std::vector<SDL_Rect>& clips){
	SDL_Rect red, blue, green, topLeft, top, topRight, center, bottomLeft, bottomRight, bottom, left, right;

	red.x = 0;
	red.y = 0;
	red.w = TILE_WIDTH;
	red.h = TILE_HEIGHT;

	clips.push_back(red);

	green.x = 0;
	green.y = 80;
	green.w = TILE_WIDTH;
	green.h = TILE_HEIGHT;

	clips.push_back(green);

	blue.x = 0;
	blue.y = 160;
	blue.w = TILE_WIDTH;
	blue.h = TILE_HEIGHT;

	clips.push_back(blue);
	
	center.x = 160;
	center.y = 80;
	center.w = TILE_WIDTH;
	center.h = TILE_HEIGHT;

	clips.push_back(center);

	top.x = 160;
	top.y = 0;
	top.w = TILE_WIDTH;
	top.h = TILE_HEIGHT;

	clips.push_back(top);

	topRight.x = 240;
	topRight.y = 0;
	topRight.w = TILE_WIDTH;
	topRight.h = TILE_HEIGHT;

	clips.push_back(topRight);
	
	right.x = 240;
	right.y = 80;
	right.w = TILE_WIDTH;
	right.h = TILE_HEIGHT;

	clips.push_back(right);

	bottomRight.x = 240;
	bottomRight.y = 160;
	bottomRight.w = TILE_WIDTH;
	bottomRight.h = TILE_HEIGHT;

	clips.push_back(bottomRight);
	
	bottom.x = 160;
	bottom.y = 160;
	bottom.w = TILE_WIDTH;
	bottom.h = TILE_HEIGHT;

	clips.push_back(bottom);

	bottomLeft.x = 80;
	bottomLeft.y = 160;
	bottomLeft.w = TILE_WIDTH;
	bottomLeft.h = TILE_HEIGHT;

	clips.push_back(bottomLeft);

	left.x = 80;
	left.y = 80;
	left.w = TILE_WIDTH;
	left.h = TILE_HEIGHT;

	clips.push_back(left);

	topLeft.x = 80;
	topLeft.y = 0;
	topLeft.w = TILE_WIDTH;
	topLeft.h = TILE_HEIGHT;

	clips.push_back(topLeft);
}


bool setObjects( std::vector<GameObject*>& objects, SdlRenderer& renderer, std::string path, std::vector<SDL_Rect>& clips)
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "lazy.map" );

    //If the map couldn't be loaded
    if( map.fail())
    {
		//Initialize the objects
        for( int i = 0; i < TOTAL_TILES; i++ )
        {
            //Put a floor tile
            objects.push_back(new Floor(x, y, renderer, path, clips[i % (TILE_BLUE + 1)]));
            
            //Move to next tile spot
            x += TILE_WIDTH;
        
            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;
            
                //Move to the next row
                y += TILE_HEIGHT;    
            }
        }
    }
	else
	{
		//Initialize the objects
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)){
				if(tileType <= 3){
					objects.push_back(new Floor(x, y, renderer, path, clips[tileType]));
				}else{
					objects.push_back(new Wall(x, y, renderer, path, clips[tileType]));
				}
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

void put_tile( std::vector<GameObject*>& objects, int objectType, SDL_Rect& camera, std::vector<SDL_Rect>& clips, SdlRenderer& renderer, std::string path)
{
    //Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState( &x, &y );
    
    //Adjust to camera
    x += camera.x;
    y += camera.y;

	for( int i = 0; i < TOTAL_TILES; i++ ){
        //Get tile's collision box
        SDL_Rect box = objects[ i ]->getBox();
        
        //If the mouse is inside the tile
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ){
            //Get rid of old tile
            delete objects[i];
			objects.erase(objects.begin() + i);

			if( objectType <= 3){
				objects.push_back(new Floor(box.x, box.y, renderer, path, clips[objectType]));
				//objects.insert(objects.begin() + i, new Floor(box.x, box.y, renderer, path, clips[objectType]));
			}else{
				objects.push_back(new Wall(box.x, box.y, renderer, path, clips[objectType]));
				//objects.insert(objects.begin() + i, new Wall(box.x, box.y, renderer, path, clips[objectType]));
			}
			break;
        }
    }
}

void show_type(SDL_Window* gWindow, int tileType )
{
    switch( tileType )
    {
        case TILE_RED:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Red Floor");
        break;
        
        case TILE_GREEN:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Green Floor");
        break;
        
        case TILE_BLUE:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Blue Floor");
        break;
        
        case TILE_CENTER:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Center Wall");
        break;
        
        case TILE_TOP:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Top Wall");
        break;
        
        case TILE_TOPRIGHT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Top Right Wall");
        break;
        
        case TILE_RIGHT:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Right Wall");
        break;
        
        case TILE_BOTTOMRIGHT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Bottom Right Wall");
        break;
        
        case TILE_BOTTOM:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Bottom Wall");
        break;
        
        case TILE_BOTTOMLEFT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Bottom Left Wall");
        break;
        
        case TILE_LEFT:
        SDL_SetWindowTitle(gWindow, "Level Designer. Current Tile: Left Wall");
        break;
        
        case TILE_TOPLEFT:
        SDL_SetWindowTitle( gWindow,"Level Designer. Current Tile: Top Left Wall");
        break;
    };    
}

void setCamera( SDL_Rect& camera )
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

void close( std::vector<GameObject*>& objects )
{
	//Deallocate objects
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( objects[ i ] != NULL )
		 {
			delete objects[ i ];
		 }
	}
}