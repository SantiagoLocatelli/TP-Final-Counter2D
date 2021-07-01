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

float Math::degreesToRadians(float degrees){
    return (degrees*180.0)/PI;
}

float Math::radiansToDegrees(float radians){
    return (radians*PI)/180.0;
}

float Math::calculateRadians(coordenada_t center, coordenada_t point){
    float radians = atan2((point.y-center.y), (point.x-center.x)) + PI;
    return radians;
}