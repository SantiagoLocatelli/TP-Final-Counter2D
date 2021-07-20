#include "ParticleBullets.h"
#include "../Managers/GameMath.h"

#define WIDTH_SHOT 5

ParticleBullets::ParticleBullets(SdlRenderer& renderer):renderer(renderer){}

void ParticleBullets::setTrajectory(Coordinate pos, Coordinate dst){

    this->pos = pos;
    this->dst = dst;
}

void ParticleBullets::render(Coordinate cam){
    this->renderer.setDrawColor(0x06, 0x06, 0x06, 120);
    this->renderer.drawLine(this->pos.x - cam.x, this->pos.y - cam.y, 
        this->dst.x - cam.x, this->dst.y - cam.y);

    this->renderer.drawLine(this->pos.x - cam.x - 1, this->pos.y - cam.y, 
        this->dst.x - cam.x, this->dst.y - cam.y);
        
    this->renderer.drawLine(this->pos.x - cam.x + 1, this->pos.y - cam.y, 
        this->dst.x - cam.x, this->dst.y - cam.y);
}