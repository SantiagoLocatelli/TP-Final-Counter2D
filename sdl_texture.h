#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "sdl_renderer.h"
class SdlTexture{
	private:
		//SDL_Renderer* mRenderer; // no se si va el objeto RAII
		SdlRenderer& renderer;
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Image dimensions
		int mWidth;
		int mHeight;

	public:
		//Initializes variables
		SdlTexture(SdlRenderer& renderer, std::string path);

		//Loads image at specified path
		//bool loadFromFile(std::string path, SDL_Renderer*& renderer);
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
             SDL_Renderer*& renderer, TTF_Font*& font);
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha(Uint8 alpha);
		
		//Renders texture at given point
		void render(int x, int y, int width, int height, SDL_Rect* clip = NULL, double angle = 0.0,
         SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void render(int x, int y);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		//Deallocates memory
		~SdlTexture();
};
#endif
