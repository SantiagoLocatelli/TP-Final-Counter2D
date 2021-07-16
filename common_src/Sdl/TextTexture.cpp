#include "TextTexture.h"

TextTexture::TextTexture(SdlRenderer& renderer, std::string path, int size):
    renderer(renderer), size({0,0}), pos({0,0}){

    if( TTF_Init() == -1 ){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    this->font = TTF_OpenFont( path.c_str(), size );
    if( this->font == NULL ){
		printf( "Failed to load the font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
    this->mTexture = NULL;
    this->size = {0, 0};
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

            this->size.w = textSurface->w;
            this->size.h = textSurface->h;

            SDL_FreeSurface(textSurface);
        }
    }
}

void TextTexture::setCoordinate(Coordinate pos) {
    this->pos = pos;
}

void TextTexture::render(Coordinate dst) {
    SDL_Rect renderQuad = {dst.x, dst.y, this->size.w, this->size.h};
    this->renderer.render(this->mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

void TextTexture::render() {

    SDL_Rect renderQuad = {this->pos.x, this->pos.y, size.w, size.h};
    this->renderer.render(this->mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

bool TextTexture::isMouseTouching(){
    //Check if mouse is in button
    bool inside = true;
	Coordinate mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);

    //Mouse is left of the button
    if (mouse.x < this->pos.x){
        inside = false;
    }
    //Mouse is right of the button
    else if (mouse.x > this->pos.x + this->size.w){
        inside = false;
    }
    //Mouse above the button
    else if (mouse.y < this->pos.y){
        inside = false;
    }
    //Mouse below the button
    else if (mouse.y > this->pos.y + this->size.h){
        inside = false;
    }

    return inside;
}


Size TextTexture::getSize(){return this->size;}

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

