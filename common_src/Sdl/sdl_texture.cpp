#include "sdl_texture.h"
#include <string>
#include <stdio.h>

SdlTexture::SdlTexture(SdlRenderer& r, int w, int h):renderer(r), mWidth(w), mHeight(h){
    SDL_Surface *surf; 
	this->mTexture = this->renderer.createTexture(w,h);
}

SdlTexture::SdlTexture(SdlRenderer& r, std::string path) : renderer(r){
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}else{
		//Create texture from surface pixels
		this->mTexture = this->renderer.createTextureFromSurface(loadedSurface);
		if (this->mTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}else{
			//Get image dimensions
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

SdlTexture::SdlTexture(SdlRenderer& r, std::string path, int type) : renderer(r){
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}else{
		//Create texture from surface pixels
		this->mTexture = this->renderer.createTextureFromSurface(loadedSurface);
		if(this->mTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}else{
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
			this->type = type;
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
		this->mTexture = this->renderer.createTextureFromSurface(loadedSurface);
		if(this->mTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}else{
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
				this->mTexture = this->renderer.createTextureFromSurface(textSurface);
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

void SdlTexture::render(int x, int y, int width, int height, double degrees)const{
	render(x, y, width, height, NULL, degrees);
}

void SdlTexture::render(int x, int y, SDL_Rect* clip, double degrees)const{
	render(x,y,this->mWidth, this->mHeight, clip, degrees);
}

void SdlTexture::render(int x, int y, int width, int height, SDL_Rect* clip, double angle,
     SDL_Point* center, SDL_RendererFlip flip)const{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, width, height};
	//Set clip rendering dimensions
	// if( clip != NULL )
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }
	//Render to screen
	this->renderer.render(this->mTexture, clip, &renderQuad, angle, center, flip);
}


int SdlTexture::getWidth()const{return this->mWidth;}
int SdlTexture::getHeight()const{return this->mHeight;}


SdlTexture& SdlTexture::operator=(SdlTexture&& other){
	this->mWidth = other.mWidth;
	this->mHeight = other.mHeight;
	this->mTexture = other.mTexture;
	this->renderer = other.renderer;
	this->type = other.type;
	return *this;
}

SdlTexture::SdlTexture(SdlTexture&& other): renderer(other.renderer){
	if (other.mTexture != NULL) {

		this->mHeight = other.mHeight;
		this->mWidth = other.mWidth;
		this->type = other.type;
		this->mTexture = other.mTexture;
		other.mTexture = NULL;
	}
}

int SdlTexture::getType()const{
	return this->type;
}

SdlTexture::~SdlTexture(){
	free();
	TTF_Quit();
	delete this->mTexture;
}
