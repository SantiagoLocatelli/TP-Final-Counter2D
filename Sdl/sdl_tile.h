#ifndef __SDL_TILE_H__
#define __SDL_TILE_H__
#include <SDL2/SDL.h>
#include "sdl_texture.h"
class Tile : public SdlTexture{
    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;

    public:
		//Initializes position and type
		Tile(int x, int y, int tileType);

		//Shows the tile
		void render(SDL_Rect& camera);

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();
};
#endif
