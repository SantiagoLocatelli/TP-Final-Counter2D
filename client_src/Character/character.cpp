#include "character.h"
#include "../Events/game_math.h"
#include <iostream>

Character::Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn, Cursor& cur)
    : area(area), an(texture), cam(cam), stn(stn), cur(cur){
}


// void Character::update(int level_width, int level_height){
//     //Move the Character left or right
//     this->area.x += this->mVelX;

//     //If the Character went too far to the left or right
//     if ((this->area.x < 0) || (this->area.x + this->area.w > level_width)){
//         //Move back
//         this->area.x -= this->mVelX;
//     }

//     //Move the Character up or down
//     this->area.y += this->mVelY;

//     //If the Character went too far up or down
//     if ((this->area.y < 0) || (this->area.y + this->area.h > level_height)){
//         //Move back
//         this->area.y -= this->mVelY;
//     }
   
//     //Center the camera over the Character SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//     this->cam.centerCamera(this->getRect());
//     //Keep the camera in bounds
//     this->cam.keepInBounds(level_width, level_height);
//     this->stn.centerStencil(this->getRect());

//     // para que cambia de frame solo si avanza
//     if (this->mVelX != 0 || this->mVelY != 0) {
//         this->an.advanceFrame();
//     }
// }

void Character::render(){
    std::cout << this->area.x << " - " << this->area.y << std::endl;
    SDL_Rect dst = {this->area.x - this->cam.getPosX() - this->area.w/2, this->area.y - this->cam.getPosY() - this->area.h/2, this->area.w, this->area.h};
    this->an.render(dst, this->cur.getDegrees());
    this->stn.render(this->cam.getPosX()+ this->area.w/2, this->cam.getPosY() + this->area.h/2, this->cur.getDegrees());
}

// void Character::moveRight(){this->mVelX += CHARACTER_VEL;}
// void Character::moveLeft(){this->mVelX -= CHARACTER_VEL;}
// void Character::moveUp(){this->mVelY -= CHARACTER_VEL;}
// void Character::moveDown(){this->mVelY += CHARACTER_VEL;}

// void Character::stopRight(){this->mVelX -= CHARACTER_VEL;}
// void Character::stopLeft(){this->mVelX += CHARACTER_VEL;}
// void Character::stopUp(){this->mVelY += CHARACTER_VEL;}
// void Character::stopDown(){this->mVelY -= CHARACTER_VEL;}

void Character::lookAt(int x, int y, int relX, int relY){
    // se le resta la pos de la camara para que resulte la psicion del jguador
    // en la screen y no del nivel.
    this->cur.lookAt(this->area.x - this->cam.getPosX(), this->area.y - this->cam.getPosY(), x, y, relX, relY);
}

int metersToPixel(float pos, int level_meters, int level_pixs){
    int porcentage = (pos*100.0)/ (double)level_meters;
    
    return (level_pixs*porcentage)/100;
}

void Character::update(const ModelInfo model, const LevelInfo level) {

    int x = metersToPixel(model.you.x, level.w_meters, level.width);
    int y = metersToPixel(model.you.y, level.h_meters, level.height);

    this->cam.centerCamera(this->getRect());
    
    this->cam.keepInBounds(level.width, level.height);
    this->stn.centerStencil(this->getRect());

    // para que cambia de frame solo si avanza
    if (this->area.x != x || this->area.y != y) {

        this->an.advanceFrame();
    }
    this->area.x = x;
    this->area.y = y;
}

int Character::getPosY(){return this->area.y;}
int Character::getPosX(){return this->area.x;}
SDL_Rect Character::getRect(){return this->area;}
