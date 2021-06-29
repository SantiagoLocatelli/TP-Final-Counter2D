#include "cursor.h"
#include "../Events/gameMath.h"
#include <cstdio>
#define SENSIBILITY 2
#define UNION_RANGE 30.0

Cursor::Cursor(int screen_w, int screen_h):screen_w(screen_w),
    screen_h(screen_h), degrees(0.0){}

void Cursor::setAt(double degrees){
    this->degrees = degrees;
}

double Cursor::getDegrees(){return this->degrees;}

/*
Devuelve verdadero si la nueva posicion del cursor no coincide
con los grados del mismo.
*/
bool changedAxis(int x, int y, double degrees) {
    return ((0 > y && degrees < 135.0 && degrees >= 45.0) ||
            (0 < y && degrees <= 315.0 && degrees > 225.0) ||
            (0 > x && (degrees < 45.0 || degrees > 315.0)) ||
            (0 < x && degrees <= 215.0 && degrees >= 135.0));
}


void Cursor::lookAt(int center_x, int center_y, MouseMotion motion){    
    // son las velocidades relativas del mouse, de como se viene moviendo

    // en este caso se le da importancia a la x
        // la velodad relativa de x es negativa si se mueve el mouse para la izquierda 
        // con respecto a la posicion anterior del mouse, por eso se le resta, para que 
        // termine aumentando los grados

    motion.x = motion.x - center_x;
    motion.y = motion.y - center_y; 

    if (motion.x == 0) {
        if (motion.y > 0) {
            this->degrees = 90.0;
        } else {
            this->degrees = 270.0;
        }
        return;
    }

    int sensibility = SENSIBILITY;
    int distance = Math::manhattanDistance({0, 0}, {motion.x, motion.y});
    
    // si le restp a la sensibilidad, quiere decir que se mueve mas rapido
    // porque lo estoy diviendo.d
    printf("distania manhattan: %i\n", distance);
    printf("coordenada, x: %i, y: %i\n", motion.x, motion.y);
    if (distance <= 50) {
        sensibility--;
        printf("se cambio la sensibilidad\n");
    }
    double degrees = (double) ((int)this->degrees % 360);
    if (degrees < 0.0){
        degrees = (360.0 + degrees);
    }

    if (degrees >= (45.0 - UNION_RANGE) && degrees < (135.0 + UNION_RANGE)) {
        degrees = degrees - (motion.relX/sensibility);
    } 

    if (degrees < (315.0 + UNION_RANGE) && degrees > (225.0 - UNION_RANGE)) {
        degrees = degrees + (motion.relX/sensibility);

    } 
    if (degrees >= (135.0 - UNION_RANGE) && degrees <= (225.0 + UNION_RANGE)) {
        degrees = degrees - (motion.relY/sensibility);
    } 

    if (degrees < (45.0 + UNION_RANGE) || degrees >= (315.0 - UNION_RANGE)) {
        degrees = degrees + (motion.relY/sensibility);
    }

    if (changedAxis(motion.x, motion.y, degrees)) {
        degrees = Math::calculateDegrees({center_x, center_y}, {motion.x, motion.y});
    }
    this->degrees = degrees;
}
