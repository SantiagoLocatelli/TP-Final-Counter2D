#ifndef __Character_H__
#define __Character_H__

#include "../../Sdl/sdl_renderer.h" 
#include "../../Sdl/sdl_texture.h"
#include "camera.h"
#include "stencil.h"
#include "animation.h"
#include <list>
#include "../../common/Protocol.h"

struct LevelInfo{
    int height;
    int width;
	int h_meters;
	int w_meters;
    std::list<Box> boxes;
};


class Character{

    private:
		
		Animation an;
		SDL_Rect area;
		Camera& cam;
		Stencil& stn;

    public:
		//Initializes the variables
		Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn);

		//Moves the Character
		// void update(int level_width, int level_height);
		void update(const ModelInfo model, const LevelInfo level);
		void update(int l_w, int l_h);
		//Shows the Character on the screen relative to the camera
		// void render( int camX, int camY );
		void render();

		SDL_Rect getRect();

		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();

		void stopRight();
		void stopLeft();
		void stopUp();
		void stopDown();

		void lookAt(int x, int y, int relX, int relY);

		//Position accessors
		int getPosX();
		int getPosY();

		Character& operator=(const Character&);
		Character(Character&& other);

};
#endif
