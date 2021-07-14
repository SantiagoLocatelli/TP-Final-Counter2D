#include "sdl_texture.h"
#include <string>
#include <stdio.h>

SdlTexture::SdlTexture(SdlRenderer& r, int w, int h, int type):renderer(r), mWidth(w), mHeight(h){
    // SDL_Surface *surf;
	this->type = type;
	this->mTexture = this->renderer.createTexture(w,h);
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

SdlTexture::SdlTexture(SdlRenderer& r, std::string path, Uint8 red, Uint8 green, Uint8 blue, int type) : renderer(r){
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
			this->type = type;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

// es para crear textura a partir de texto
SdlTexture::SdlTexture(SdlRenderer& renderer, SDL_Surface* surface, int type):renderer(renderer){
	this->type = type;
	this->mTexture = this->renderer.createTextureFromSurface(surface);
}


SdlTexture::SdlTexture(SdlRenderer& r, std::string path, int size, std::string textureText, Uint8 red,
 Uint8 green, Uint8 blue, int type) : renderer(r){
	this->type = type;
	this->mTexture = NULL;
	if (TTF_Init() == -1){
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}else{
		changeTextTexture(textureText, path, size, red, green, blue);
	}
}

int SdlTexture::changeTextTexture(std::string text, std::string path, int size, Uint8 red,
 Uint8 green, Uint8 blue){
	if (this->mTexture != NULL){
		SDL_DestroyTexture(this->mTexture);
	}
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	if (font == NULL){
		printf("Failed to load %s font! SDL_ttf Error: %s\n", path.c_str(), TTF_GetError());
	}else{
		//Render text surface
		SDL_Color textColor = {red, green, blue};
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		if (textSurface != NULL){
			//Create texture from surface pixels
			this->mTexture = this->renderer.createTextureFromSurface(textSurface);
			if (this->mTexture == NULL){
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}else{
				//Get image dimensions
				mWidth = textSurface->w;
				mHeight = textSurface->h;
				SDL_FreeSurface(textSurface);
				TTF_CloseFont(font);
				return 0;
			}
			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}else{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}
	return -1;
}


void SdlTexture::free(){
	if(this->mTexture != NULL){
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

void SdlTexture::renderFlip(int x, int y, SDL_RendererFlip flip)const{
	render(x, y, this->mWidth, this->mHeight, NULL, 0.0, NULL,flip);
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

bool SdlTexture::isMouseTouching(int posX, int posY){
    //Check if mouse is in button
    bool inside = true;
	int mousePosX, mousePosY;
	SDL_GetMouseState(&mousePosX, &mousePosY);

    //Mouse is left of the button
    if (mousePosX < posX){
        inside = false;
    }
    //Mouse is right of the button
    else if (mousePosX > posX + this->mWidth){
        inside = false;
    }
    //Mouse above the button
    else if (mousePosY < posY){
        inside = false;
    }
    //Mouse below the button
    else if (mousePosY > posY + this->mHeight){
        inside = false;
    }

    return inside;
}

bool SdlTexture::isMouseTouching(int posX, int posY, int width, int height){
    //Check if mouse is in button
    bool inside = true;
	int mousePosX, mousePosY;
	SDL_GetMouseState(&mousePosX, &mousePosY);

    //Mouse is left of the button
    if (mousePosX < posX){
        inside = false;
    }
    //Mouse is right of the button
    else if (mousePosX > posX + width){
        inside = false;
    }
    //Mouse above the button
    else if (mousePosY < posY){
        inside = false;
    }
    //Mouse below the button
    else if (mousePosY > posY + height){
        inside = false;
    }

    return inside;
}

void SdlTexture::setWidthAndHeight(int width, int height){
	this->mWidth = width;
	this->mHeight = height;
}

int SdlTexture::getWidth()const{return this->mWidth;}
int SdlTexture::getHeight()const{return this->mHeight;}

SdlTexture& SdlTexture::operator=(const SdlTexture& other){
	if (other.mTexture != NULL) {
		this->mWidth = other.mWidth;
		this->type = other.type;
		this->renderer = other.renderer;
		this->mTexture = other.mTexture;
		this->mHeight = other.mHeight;
		//this->path = other.path;
	}
	return *this;
}


SdlTexture& SdlTexture::operator=(SdlTexture&& other){
	if (this->mTexture != NULL) {

		this->mWidth = other.mWidth;
		this->mHeight = other.mHeight;
		this->mTexture = other.mTexture;
		this->renderer = other.renderer;
		this->type = other.type;
		other.mTexture = NULL;
	}
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

SDL_Texture* SdlTexture::createTexture(int w, int h){
	return this->renderer.createTexture(w, h);
}

SdlTexture::~SdlTexture(){
	if (this->mTexture != NULL) {
		free();
		TTF_Quit();
	}
}
