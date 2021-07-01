#include "gameMath.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

int productoEscalar(coordenada_t coord1, coordenada_t coord2){
    return ((coord1.x*coord2.x)+(coord1.y*coord2.y));
}

int modulo(coordenada_t coord){
    return sqrt((coord.x*coord.x) + (coord.y*coord.y));
}

bool coordsIguales(coordenada_t coord1, coordenada_t coord2){
    return ((coord1.x == coord2.x) && (coord1.y == coord2.y));
}

int Math::manhattanDistance(coordenada_t point1, coordenada_t point2){
    return (abs(point1.x - point2.x) + abs(point1.y - point2.y));
}


float Math::calculateRadians(coordenada_t center, coordenada_t point){

    /*
    recordando que centramos el stencil en el personale.
    la idea es pensar en tres puntos, para generar dos lineas.
    se sabe que si los degrees son 0, entonces el stencil mira para la derecha.
    por lo que imaginamos un eje de coordenadas con la pos del stencil como centro,
    la pos del stencil es nuestro primer punto, el segundo viene a ser la pos del mouse,
    y el tercer punto lo generamos con la pos en y del personaje, y la pos en x del mouse.
    y calculamos los angulos entre esas dos lineas
    */
    double degrees = 0.0;
    coordenada_t newVec = {point.x, center.y};

    if (point.x == 0) {
        point.x = 1;
    }

    if (!coordsIguales(center, newVec) && !coordsIguales(center, point)) {

        int moduloPoint = modulo(point);
        int moduloNewVec = modulo(newVec);
        double result = (double)productoEscalar(point, newVec)/ (moduloPoint*moduloNewVec);
        
        if (moduloPoint != moduloNewVec) {

            // acos devuelve el resultado en radianes
            result = acos(result)*180.0/PI;
            degrees = result;

            if (point.x < 0.0 && point.y < 0.0) {
                degrees += 180.0;
            } else if (point.x < 0.0 && point.y > 0.0) {
                degrees = 180.0 - degrees;
            } else if (point.x > 0.0 && point.y < 0.0) {
                degrees = 360.0 - degrees;
            } 
        }
    } else {
        degrees += 180.0; 
    }

    float radians = (degrees * PI)/180.0;

    return radians;
}