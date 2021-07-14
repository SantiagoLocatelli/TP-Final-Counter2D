#include "TextTexture.h"

TextTexture::TextTexture(SdlRenderer& renderer, std::string path, int size):
    renderer(renderer), width(0), height(0){

    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    this->font = TTF_OpenFont( path.c_str(), size );
    if( this->font == NULL ){
		printf( "Failed to load the font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
    this->mTexture = NULL;
}

void TextTexture::setText(std::string text, struct Color color){
    SDL_Surface* textSurface = TTF_RenderText_Solid( this->font, text.c_str(), {color.r,color.g,color.b});
    if (textSurface == NULL) {
        printf( "No se pudo crear la textura: %s. SDL_ttf Error: %s\n", text.c_str(), TTF_GetError() );
    } else {
        if (this->mTexture != NULL) {
            SDL_DestroyTexture( this->mTexture );
        }
        this->mTexture = this->renderer.createTextureFromSurface(textSurface);
        if (this->mTexture == NULL){
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }else{

            width = textSurface->w;
            height = textSurface->h;
            SDL_FreeSurface(textSurface);
        }
    }
}

void TextTexture::render(Coordinate dst) {

    SDL_Rect renderQuad = {dst.x - width, dst.y - height, width, height};
    this->renderer.render(this->mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

TextTexture::~TextTexture(){
    if(this->mTexture != NULL){
		SDL_DestroyTexture( this->mTexture );
		this->mTexture = NULL;
    }
    if (this->font != NULL){
        //TTF_CloseFont(this->font); 
        TTF_Quit();
        this->font = NULL;
    }
}

