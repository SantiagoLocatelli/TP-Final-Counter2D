#include "particleBullets.h"
#include "../Events/gameMath.h"

#define WIDTH_SHOT 5

ParticleBullets::ParticleBullets(SdlRenderer& renderer):renderer(renderer){}

void ParticleBullets::setTrajectory(Coordenada pos, Coordenada dst){

    this->pos = pos;
    this->dst = dst;
}

void ParticleBullets::render(Coordenada cam){
    this->renderer.setDrawColor(0x06, 0x06, 0x06, 120);
    this->renderer.drawLine(this->pos.x - cam.x, this->pos.y - cam.y, 
        this->dst.x - cam.x, this->dst.y - cam.y);

    this->renderer.drawLine(this->pos.x - cam.x - 1, this->pos.y - cam.y, 
        this->dst.x - cam.x, this->dst.y - cam.y);

}