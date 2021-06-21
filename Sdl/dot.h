#ifndef __DOT_H__
#define __DOT_H__
#include <SDL2/SDL.h>
#include "sdl_renderer.h" 
#include "sdl_texture.h"
#include "camera.h"
#include "stencil.h"

class Dot{

    private:
		//The X and Y offsets of the dot

		//The velocity of the dot
		int mVelX, mVelY;
		int posX, posY;
		//dimensions of the dot
		SdlTexture& texture;
		Camera& cam;
		Stencil& stn;

    public:
		//Initializes the variables
		Dot(int posX, int posY, SdlTexture& texture, Camera& cam, Stencil& stn);

		void setTexture(SdlTexture& texture);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(int level_width, int level_height);

		//Shows the dot on the screen relative to the camera
		// void render( int camX, int camY );
		void render();

		SDL_Rect getRect();

		//Position accessors
		int getPosX();
		int getPosY();

};
#endif
