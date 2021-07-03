#include "particleBullets.h"
#include "../Events/gameMath.h"

#define WIDTH_SHOT 5
#define SHOT_PATH "../../common_src/img/shot.png"

ParticleBullets::ParticleBullets(SdlRenderer& renderer):particle(renderer, SHOT_PATH){}

void ParticleBullets::setTrajectory(LevelInfo level, Bullet bullet){
    this->posX = Math::ruleOfThree(bullet.start_x, level.w_meters, level.width);
    this->posY = Math::ruleOfThree(bullet.start_y, level.h_meters, level.height);
    this->degrees = Math::radiansToDegrees(bullet.angle);
    this->distance = Math::ruleOfThree(bullet.distance, level.w_meters, level.width);
    printf("Disparo: x: %i, y: %i, grados: %f, distancia: %i\n", this->posX, this->posY, this->degrees, this->distance);
}

void ParticleBullets::render(){
    this->particle.render(this->posX, this->posY, this->distance, WIDTH_SHOT, this->degrees);
}