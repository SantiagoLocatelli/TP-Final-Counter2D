#ifndef __Character_H__
#define __Character_H__

#include "../../common_src/Sdl/sdl_renderer.h" 
#include "../../common_src/Sdl/sdl_texture.h"
#include "camera.h"
#include "stencil.h"
#include "animation.h"
#include <list>
#include "../../common_src/Protocol.h"

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
		double degrees;

    public:
		Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn);


		void update(const ModelInfo model, const LevelInfo level);
		void render();

		SDL_Rect getRect();

		void lookAt(int x, int y, int relX, int relY);

		int getPosX();
		int getPosY();

		int getRelativePosX();
		int getRelativePosY();

		Character& operator=(const Character&);
		Character(Character&& other);
};
#endif
