#include "cursor.h"
#include "game_math.h"
#include <cstdio>

#define SENSIBILITY 2
#define UNION_RANGE 30.0

Cursor::Cursor(int screen_w, int screen_h):screen_w(screen_w),
    screen_h(screen_h), degrees(0.0){}

void Cursor::setAt(double degrees){
    this->degrees = degrees;
}

double Cursor::getDegrees(){return this->degrees;}

bool changedAxis(int x, int y, double degrees) {
    return ((0 > y && degrees < 135.0 && degrees >= 45.0) ||
            (0 < y && degrees <= 315.0 && degrees > 225.0) ||
            (0 > x && (degrees < 45.0 || degrees > 315.0)) ||
            (0 < x && degrees <= 215.0 && degrees >= 135.0));
}


void Cursor::lookAt(int x, int y, int relX, int relY){    
    // son las velocidades relativas del mouse, de como se viene moviendo

    // en este caso se le da importancia a la x
        // la velodad relativa de x es negativa si se mueve el mouse para la izquierda 
        // con respecto a la posicion anterior del mouse, por eso se le resta, para que 
        // termine aumentando los grados

    x = x - (this->screen_w/2);
    y = y - (this->screen_h/2);

    if (x == 0) {
        if (y > 0) {
            this->degrees = 90.0;
        } else {
            this->degrees = 270.0;
        }
        return;
    }

    double degrees = (double) ((int)this->degrees % 360);
    if (degrees < 0.0){
        degrees = (360.0 + degrees);
    }

    if (degrees >= (45.0 - UNION_RANGE) && degrees < (135.0 + UNION_RANGE)) {
        degrees = degrees - (relX/SENSIBILITY);
    } 

    if (degrees < (315.0 + UNION_RANGE) && degrees > (225.0 - UNION_RANGE)) {
        degrees = degrees + (relX/SENSIBILITY);

    } 
    if (degrees >= (135.0 - UNION_RANGE) && degrees <= (225.0 + UNION_RANGE)) {
        degrees = degrees - (relY/SENSIBILITY);
    } 

    if (degrees < (45.0 + UNION_RANGE) || degrees >= (315.0 - UNION_RANGE)) {
        degrees = degrees + (relY/SENSIBILITY);
    }

    if (changedAxis(x, y, degrees)) {
        degrees = Math::calculateDegrees({this->screen_w/2, this->screen_h/2}, {x, y});
    }
    this->degrees = degrees;
}
