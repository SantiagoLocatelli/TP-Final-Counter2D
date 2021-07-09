#include "sdl_ttf.h"

SdlTtf::SdlTtf(SdlRenderer& renderer, std::string path, int size):renderer(renderer){
    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    this->font = TTF_OpenFont( path.c_str(), size );
    if( this->font == NULL ){
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
}

SdlTtf::~SdlTtf(){
    if (this->font != NULL){
        TTF_CloseFont(this->font);
        this->font = NULL;
        TTF_Quit();
    }
}

SdlTexture SdlTtf::createTextureFromText(std::string text, struct Color color){
    SDL_Surface* textSurface = TTF_RenderText_Solid( this->font, text.c_str(), {color.r,color.g,color.b});
	if( textSurface == NULL ){
		printf( "No se pudo crear la textura. SDL_ttf Error: %s\n", TTF_GetError() );
	}
    SdlTexture texture(this->renderer, textSurface);
    SDL_FreeSurface( textSurface );
    return texture;
;}
