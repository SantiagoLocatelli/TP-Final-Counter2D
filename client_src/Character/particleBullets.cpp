#include "particleBullets.h"
#include "../Events/gameMath.h"

#define WIDTH_SHOT 5
#define SHOT_PATH "../../common_src/img/shot.png"

ParticleBullets::ParticleBullets(SdlRenderer& renderer):renderer(renderer){}

void ParticleBullets::setTrajectory(LevelInfo level, Bullet bullet, int camX, int camY){

    this->posX = Math::ruleOfThree(bullet.pos.x, level.w_meters, level.width) - camX;
    this->posY = Math::ruleOfThree(bullet.pos.y, level.h_meters, level.height) - camY;
    int distance = Math::ruleOfThree(bullet.distance, level.w_meters, level.width);
    this->dstPosX = Math::cosOppHyp(bullet.angle, distance) + this->posX;
    this->dstPosY = Math::senoOppHyp(bullet.angle, distance) + this->posY;

}

void ParticleBullets::render(){
    this->renderer.setDrawColor(0x06, 0x06, 0x06, 120);
    this->renderer.drawLine(this->posX, this->posY, this->dstPosX, this->dstPosY);
}