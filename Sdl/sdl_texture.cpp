#include "sdl_texture.h"
#include <string>
#include <stdio.h>

SdlTexture::SdlTexture(SdlRenderer& r, std::string path) : renderer(r){
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}else{
		//Create texture from surface pixels
		this->mTexture = this->renderer.createTexture(loadedSurface);
		if(this->mTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}else{
			//Get image dimensions
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

SdlTexture::SdlTexture(SdlRenderer& r, std::string path, Uint8 red, Uint8 green, Uint8 blue) : renderer(r){
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue));
		//Create texture from surface pixels
		this->mTexture = this->renderer.createTexture(loadedSurface);
		if(this->mTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}else{
			//Get image dimensions
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

SdlTexture::SdlTexture(SdlRenderer& r, std::string path, int size, std::string textureText, Uint8 red,
 Uint8 green, Uint8 blue) : renderer(r){
	
	if (TTF_Init() == -1){
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}else{
		TTF_Font* font = TTF_OpenFont(path.c_str(), size);
		if (font == NULL){
			printf("Failed to load %s font! SDL_ttf Error: %s\n", path.c_str(), TTF_GetError());
		}else{
			//Render text surface
			SDL_Color textColor = {red, green, blue};
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
			if (textSurface != NULL){
				//Create texture from surface pixels
				this->mTexture = this->renderer.createTexture(textSurface);
				if (this->mTexture == NULL){
					printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
				}else{
					//Get image dimensions
					mWidth = textSurface->w;
					mHeight = textSurface->h;
				}
				//Get rid of old surface
				SDL_FreeSurface(textSurface);
			}else{
				printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			}
		}
	}
}

void SdlTexture::free(){
	if( this->mTexture != NULL )
	{
		SDL_DestroyTexture( this->mTexture );
		this->mTexture = NULL;
		this->mWidth = 0;
		this->mHeight = 0;
	}
}

void SdlTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(this->mTexture, red, green, blue);
}

void SdlTexture::setBlendMode( SDL_BlendMode blending ){
	SDL_SetTextureBlendMode(this->mTexture, blending);
}

void SdlTexture::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(this->mTexture, alpha);
}

void SdlTexture::render(int x, int y){
	render(x,y,this->mWidth, this->mHeight);
}

void SdlTexture::render(int x, int y, int width, int height, SDL_Rect* clip, double angle,
     SDL_Point* center, SDL_RendererFlip flip){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, width, height};
	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	this->renderer.render(this->mTexture, clip, &renderQuad, angle, center, flip);
	//SDL_RenderCopyEx(renderer, this->mTexture, clip, &renderQuad, angle, center, flip);
}

int SdlTexture::getWidth(){
	return this->mWidth;
}

int SdlTexture::getHeight(){
	return this->mHeight;
}

SdlTexture::~SdlTexture(){
	free();
	TTF_Quit();
	delete this->mTexture;
}
