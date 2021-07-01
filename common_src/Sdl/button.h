#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "sdl_texture.h"
#include <SDL2/SDL.h>
#include <vector>
class SdlButton{
	private:

		SdlTexture* mCurrentSprite;

		//Top left position
		SDL_Point mPosition;

        int mHeight, mWidth;

        //std::vector<SdlTexture> textures;

	public:
		//Initializes internal variables
		explicit SdlButton(SdlTexture* texture, int x, int y);

        //SdlButton(SdlButton&& other);

		//Sets top left position
		void setPosition(int x, int y);

		//Handles mouse event
		void handleEvent(SDL_Event* e);
	
		//Shows button sprite
		void render();

        ~SdlButton();
};
#endif
