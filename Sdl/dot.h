#ifndef __DOT_H__
#define __DOT_H__
#include <SDL2/SDL.h>
class Dot{

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//dimensions of the dot
		int mWidth, mHeight;

    public:
		//Initializes the variables
		Dot(int posX, int posY, int width, int height);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(int level_width, int level_height);

		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY );

		//Position accessors
		int getPosX();
		int getPosY();
};
#endif
