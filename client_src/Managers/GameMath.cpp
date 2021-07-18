#include "GameMath.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int productoEscalar(Coordinate coord1, Coordinate coord2){
    return ((coord1.x*coord2.x)+(coord1.y*coord2.y));
}

int modulo(Coordinate coord){
    return sqrt((coord.x*coord.x) + (coord.y*coord.y));
}

bool Math::equalCoords(Coordinate coord1, Coordinate coord2){
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

int Math::manhattanDistance(Coordinate point1, Coordinate point2){
    return (abs(point1.x - point2.x) + abs(point1.y - point2.y));
}

float Math::degreesToRadians(float degrees){
    return degrees*(PI/180.0);
}

float Math::radiansToDegrees(float radians){
    return radians* (180.0/PI);
}

float Math::calculateRadians(Coordinate center, Coordinate point){
    float radians = atan2(-(point.y-center.y), -(point.x-center.x)) + PI;
    return radians;
}

int Math::metersToPixels(float x_f, float total_f, int total_i){
    int porcentage = (x_f*100.0)/total_f;
    return (total_i*porcentage)/100;
}

float Math::pixelsToMeters(int pixels, int totalPixels, float totalMeters) {
    int porcentage = (pixels*100)/totalPixels;
    return (totalMeters*porcentage)/100.0;
}


int Math::senoOppHyp(float radians, int hypotenuse){
    return (int)(sin(radians) * (float)hypotenuse);
}

int Math::cosAdHyp(float radians, int hypotenuse){
    return (int)(cos(radians) * (float)hypotenuse);
}

int Math::getRandomNumberBetween(int min, int max){
    return ((rand() % (1+max-min)) + min);
}

int Math::pythagoras(int cat1, int cat2){
    return sqrt((cat1*cat1) + (cat2*cat2));
}
