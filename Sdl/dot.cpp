#include "dot.h"
#define DOT_VEL 10


Dot::Dot(int posX, int posY, SdlTexture& texture)
    :posX(posX), posY(posY), texture(texture){
    this->mVelX = 0;
    this->mVelY = 0;
}

void Dot::setTexture(SdlTexture& texture){
    this->texture = texture;
}


void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move(int level_width, int level_height){
    //Move the dot left or right
    this->posX += this->mVelX;

    //If the dot went too far to the left or right
    if ((this->posX < 0) || (this->posX + this->texture.getWidth() > level_width)){
        //Move back
        this->posX -= this->mVelX;
    }

    //Move the dot up or down
    this->posY += this->mVelY;

    //If the dot went too far up or down
    if ((this->posY < 0) || (this->posY + this->texture.getHeight() > level_height)){
        //Move back
        this->posY -= this->mVelY;
    }
   
}

SDL_Rect Dot::getRect(){
    return {this->posX, this->posY, this->texture.getWidth(), this->texture.getHeight()};
}

void Dot::render(int camX, int camY){
    
    this->texture.render(this->posX - camX , this->posY - camY );
}

int Dot::getPosY(){
    return this->posY;
}

int Dot::getPosX(){
    return this->posX;
}
