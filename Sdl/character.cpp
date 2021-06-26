#include "character.h"
#include "game_math.h"

#define CHARACTER_VEL 10

Character::Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn)
    : area(area), an(texture), cam(cam), stn(stn){
    this->mVelX = 0;
    this->mVelY = 0;
}


void Character::update(int level_width, int level_height){
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

    // para que cambia de frame solo si avanza
    if (this->mVelX != 0 || this->mVelY != 0) {
        this->an.advanceFrame();
    }
}

void Character::render(){
    SDL_Rect dst = {this->area.x - this->cam.getPosX(), this->area.y - this->cam.getPosY(), this->area.w, this->area.h};
    this->an.render(dst, this->cur.getDegrees());
    this->stn.render(this->cam.getPosX(), this->cam.getPosY(), this->cur.getDegrees());
}

void Character::moveRight(){this->mVelX += CHARACTER_VEL;}
void Character::moveLeft(){this->mVelX -= CHARACTER_VEL;}
void Character::moveUp(){this->mVelY -= CHARACTER_VEL;}
void Character::moveDown(){this->mVelY += CHARACTER_VEL;}

void Character::stopRight(){this->mVelX -= CHARACTER_VEL;}
void Character::stopLeft(){this->mVelX += CHARACTER_VEL;}
void Character::stopUp(){this->mVelY += CHARACTER_VEL;}
void Character::stopDown(){this->mVelY -= CHARACTER_VEL;}

void Character::lookAt(int x, int y, int relX, int relY){

    this->cur.lookAt(x - this->cam.getWidth()/2, y - this->cam.getHeight()/2, relX, relY);
}

int Character::getPosY(){return this->area.y;}
int Character::getPosX(){return this->area.x;}
SDL_Rect Character::getRect(){return this->area;}
