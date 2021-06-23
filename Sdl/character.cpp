#include "character.h"
#define CHARACTER_VEL 10


Character::Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn)
    : area(area), an(texture), cam(cam), stn(stn){
    this->mVelX = 0;
    this->mVelY = 0;
}




void Character::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: mVelY -= CHARACTER_VEL; break;
            case SDLK_DOWN: mVelY += CHARACTER_VEL; break;
            case SDLK_LEFT: mVelX -= CHARACTER_VEL; break;
            case SDLK_RIGHT: mVelX += CHARACTER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: mVelY += CHARACTER_VEL; break;
            case SDLK_DOWN: mVelY -= CHARACTER_VEL; break;
            case SDLK_LEFT: mVelX += CHARACTER_VEL; break;
            case SDLK_RIGHT: mVelX -= CHARACTER_VEL; break;
        }
    } else if (e.type == SDL_MOUSEMOTION) {
        this->stn.handleEvent(e);
    }
}

void Character::move(int level_width, int level_height){
    //Move the Character left or right
    this->area.x += this->mVelX;

    //If the Character went too far to the left or right
    if ((this->area.x < 0) || (this->area.x + this->area.w > level_width)){
        //Move back
        this->area.x -= this->mVelX;
    }

    //Move the Character up or down
    this->area.y += this->mVelY;

    //If the Character went too far up or down
    if ((this->area.y < 0) || (this->area.y + this->area.h > level_height)){
        //Move back
        this->area.y -= this->mVelY;
    }
   
    //Center the camera over the Character SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    this->cam.centerCamera(this->getRect());
    //Keep the camera in bounds
    this->cam.keepInBounds(level_width, level_height);
    this->stn.centerStencil(this->getRect());
}

SDL_Rect Character::getRect(){
    return {this->area.x, this->area.y, this->area.w, this->area.h};
}

void Character::render(){
    SDL_Rect dst = {this->area.x - this->cam.getPosX(), this->area.y - this->cam.getPosY(), this->area.w, this->area.h};
    this->an.render(dst, this->degrees);
    this->stn.render(this->cam.getPosX(), this->cam.getPosY());
}

int Character::getPosY(){
    return this->area.y;
}

int Character::getPosX(){
    return this->area.x;
}
