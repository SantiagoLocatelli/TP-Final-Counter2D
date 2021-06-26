#include "cursor.h"
#include "game_math.h"
#include <cstdio>

#define SENSIBILITY 2

Cursor::Cursor():x(0), y(0), degrees(0.0){}

void Cursor::setAt(int x, int y, double degrees){
    this->x = x;
    this->y = y;
    this->degrees = degrees;
}

double Cursor::getDegrees(){return this->degrees;}

void Cursor::lookAt(int x, int y, int relX, int relY){    
    // son las velocidades relativas del mouse, de como se viene moviendo

    // en este caso se le da importancia a la x
        // la velodad relativa de x es negativa si se mueve el mouse para la izquierda 
        // con respecto a la posicion anterior del mouse, por eso se le resta, para que 
        // termine aumentando los grados


    double degrees = (double) ((int)this->degrees % 360);
    if (degrees < 0.0){
        degrees = (360.0 + degrees);
    }

    if (degrees >= 45.0 && degrees < 135.0) {
        degrees = degrees - (relX/SENSIBILITY);
        printf("entro 1\n");
        printf("grados: %.2f\n", this->degrees);
        printf("this->y: %i, y: %i\n", this->y ,y);

        if (0 > y && this->y < 0) {
            printf("grados: %.2f\n", degrees);
            degrees = Math::calculateDegrees({this->x, this->y}, {x, y});
        }
    } else if (degrees < 315.0 && degrees > 225.0) {
        degrees = degrees + (relX/SENSIBILITY);
        printf("entro 2\n");
        // printf("x: %i, y: %i\n", x ,y);

        if (0 < y && this->y > 0) {
            degrees = Math::calculateDegrees({this->x, this->y}, {x, y});
            printf("grados: %.2f\n", degrees);
        }
    } else if (degrees >= 135.0 && degrees <= 225.0) {
        degrees = degrees - (relY/SENSIBILITY);
        printf("entro 3\n");
        // printf("x: %i, y: %i\n", x ,y);
        
        if (0 < x && this->x > 0) {
            printf("grados: %.2f\n" , degrees);
            degrees = Math::calculateDegrees({this->x, this->y}, {x, y});
        }
    } else {
        degrees = degrees + (relY/SENSIBILITY);
        printf("entro 4\n");
        // printf("x: %i, y: %i\n", x ,y);

        if (0 > x && this->x < 0) {
            printf("grados: %.2f\n", degrees);
            degrees = Math::calculateDegrees({this->x, this->y}, {x, y});
        }
    }
    this->x = x;
    this->y = y;
    this->degrees = degrees;
}
