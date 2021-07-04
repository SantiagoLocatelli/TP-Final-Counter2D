#include "particleBullets.h"
#include "../Events/gameMath.h"

#define WIDTH_SHOT 5
#define SHOT_PATH "../../common_src/img/shot.png"

ParticleBullets::ParticleBullets(SdlRenderer& renderer):renderer(renderer){}

void ParticleBullets::setTrajectory(LevelInfo level, Bullet bullet, int camX, int camY){

    this->posX = Math::ruleOfThree(bullet.start_x, level.w_meters, level.width) - camX;
    this->posY = Math::ruleOfThree(bullet.start_y, level.h_meters, level.height) - camY;
    int distance = Math::ruleOfThree(bullet.distance, level.w_meters, level.width);
    this->dstPosX = Math::cosOppHyp(bullet.angle, distance) + this->posX;
    this->dstPosY = Math::senoOppHyp(bullet.angle, distance) + this->posY;
    printf("coordenada src: x: %i, y: %i\n", Math::ruleOfThree(bullet.start_x, level.w_meters, level.width), Math::ruleOfThree(bullet.start_y, level.h_meters, level.height));
    printf("angulo: %f\n", bullet.angle);

}

void ParticleBullets::render(){
    this->renderer.setDrawColor(0x66, 0x66, 0x66, 120);
    printf("coordenada dst: x: %i, y: %i\n", this->dstPosX, this->dstPosY);
    this->renderer.drawLine(this->posX, this->posY, this->dstPosX, this->dstPosY);
}