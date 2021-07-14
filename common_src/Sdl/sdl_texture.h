#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "sdl_renderer.h"

class SdlTexture{
	private:
		SdlRenderer& renderer;
		SDL_Texture* mTexture;

		int type;
		int mWidth;
		int mHeight;

	public:
		//Initializes variables
		SdlTexture(SdlRenderer& r, int w, int h);
		SdlTexture(SdlRenderer& renderer, std::string path);
		SdlTexture(SdlRenderer& renderer, SDL_Surface* surface);
		SdlTexture(SdlRenderer& renderer, std::string path, Uint8 red, Uint8 green, Uint8 blue);
		SdlTexture(SdlRenderer& renderer, std::string path, int size, std::string textureText, Uint8 red,
 			Uint8 green, Uint8 blue);

		SdlTexture(SdlRenderer& r, std::string path, int type);

		int changeTextTexture(std::string text, std::string path, int size, Uint8 red, Uint8 green, Uint8 blue);

		bool isMouseTouching(int posX, int posY);
		bool isMouseTouching(int posX, int posY, int width, int height);

		//Loads image at specified path
		//bool loadFromFile(std::string path, SDL_Renderer*& renderer);
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
             SDL_Renderer*& renderer, TTF_Font*& font);
		#endif

		void free();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha(Uint8 alpha);
		
		void render(int x, int y, int width, int height, SDL_Rect* clip = NULL, double angle = 0.0,
        	SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)const;

		void render(int x, int y, SDL_Rect* clip = NULL, double degrees = 0.0)const;
		void render(int x, int y, int width, int height, double degrees)const;

		void renderFlip(int x, int y, SDL_RendererFlip flip)const;
		
		void setWidthAndHeight(int width, int height);

		SDL_Texture* createTexture(int w, int h);


		int getWidth() const;
		int getHeight() const;
    	int getType() const;

		SdlTexture& operator=(const SdlTexture&);
		SdlTexture& operator=(SdlTexture&&);
		SdlTexture(SdlTexture&& other);
		~SdlTexture();

};
#endif
