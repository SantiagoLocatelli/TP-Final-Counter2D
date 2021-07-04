#include "particleBullets.h"
#include "../Events/gameMath.h"

#define WIDTH_SHOT 5
#define SHOT_PATH "../../common_src/img/shot.png"

ParticleBullets::ParticleBullets(SdlRenderer& renderer):renderer(renderer){}

void ParticleBullets::setTrajectory(LevelInfo level, Bullet bullet){
    printf("coordenada src en metros: x: %f, y: %f\n", bullet.start_x, bullet.start_y);

    this->posX = Math::ruleOfThree(bullet.start_x, level.w_meters, level.width);
    this->posY = Math::ruleOfThree(bullet.start_y, level.h_meters, level.height);
    printf("coordenada src: x: %i, y: %i\n", Math::ruleOfThree(bullet.start_x, level.w_meters, level.width), Math::ruleOfThree(bullet.start_y, level.h_meters, level.height));
    int distance = Math::ruleOfThree(bullet.distance, level.w_meters, level.width);
    this->dstPosX = Math::senoOppHyp(bullet.angle, distance);
    this->dstPosY = Math::cosOppHyp(bullet.angle, distance);


}

void ParticleBullets::render(){
    this->renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    // printf("coordenada src: x: %i, y: %i\n", this->posX, this->posY);
    printf("coordenada dst: x: %i, y: %i\n", this->dstPosX, this->dstPosY);
    this->renderer.drawLine(this->posX, this->posY, this->dstPosX, this->dstPosY);
}