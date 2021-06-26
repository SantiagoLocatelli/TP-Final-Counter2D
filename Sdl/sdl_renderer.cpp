#include "sdl_renderer.h"
#include <stdio.h>

SdlRenderer::SdlRenderer(SdlWindow* window){
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf( "Warning: Linear texture filtering not enabled!");
	}else{
        this->mRenderer = window->createRender();
        if(this->mRenderer == NULL){
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }else{
            SDL_SetRenderDrawColor(this->mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            
            //Initialize PNG loading
            //No se si es correcto que este en esta clase
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }
        }
    }
}


SDL_Texture* SdlRenderer::createTexture(int w, int h){
    return SDL_CreateTexture(this->mRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);
}
SDL_Texture* SdlRenderer::createTextureFromSurface(SDL_Surface* loadedSurface){
    return SDL_CreateTextureFromSurface(this->mRenderer, loadedSurface);
}

void SdlRenderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha){
    SDL_SetRenderDrawColor(this->mRenderer, r, g, b, alpha);
}

SDL_Texture* SdlRenderer::getRenderTarget(){
    return SDL_GetRenderTarget(this->mRenderer);
}

int SdlRenderer::setRenderTarget(SDL_Texture* target){
    return SDL_SetRenderTarget(this->mRenderer, target);
}

void SdlRenderer::clear(){
    SDL_RenderClear(this->mRenderer);
}

void SdlRenderer::updateScreen(){
    SDL_RenderPresent(this->mRenderer);
}

void SdlRenderer::render(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_RenderCopyEx(this->mRenderer, texture, clip, renderQuad, angle, center, flip);
}

int SdlRenderer::renderCopy(SDL_Texture* target){
    SDL_RenderCopy(this->mRenderer, target, NULL, NULL);
}

int SdlRenderer::renderReadPixels(void* pixels, int w, int format){
    return SDL_RenderReadPixels(this->mRenderer, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
}

SdlRenderer::~SdlRenderer(){
    SDL_DestroyRenderer(this->mRenderer);
    IMG_Quit();
}
