#include "game_math.h"
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


double Math::calculateDegrees(coordenada_t center, coordenada_t point){
    system("clear");
    printf("vel x relative: %i\n", point.x);
    printf("vel y relative: %i\n", point.y);


    /*
    recordando que centramos el stencil en el personale.
    la idea es pensar en tres puntos, para generar dos lineas.
    se sabe que si los degrees son 0, entonces el stencil mira para la derecha.
    por lo que imaginamos un eje de coordenadas con la pos del stencil como centro,
    la pos del stencil es nuestro primer punto, el segundo viene a ser la pos del mouse,
    y el tercer punto lo generamos con la pos en y del personaje, y la pos en x del mouse.
    y calculamos los angulos entre esas dos lineas
    */
    double degrees = 0;
    coordenada_t origen = {0, 0};
    coordenada_t newCoord = {point.x, center.y};
    // para obtener los vectores dobe restar los puntos
    coordenada_t newVec = {newCoord.x - center.x, newCoord.y - center.y};
    coordenada_t pointVec = {point.x - center.x, point.y - center.y};

    if (!coordsIguales(origen, pointVec) && !coordsIguales(origen, newVec)) {

        int moduloNewVec = modulo(newVec);
        int moduloPointVec = modulo(pointVec);
        double result = (double)productoEscalar(newVec, pointVec)/ (moduloNewVec*moduloPointVec);
        if ((moduloNewVec == moduloPointVec) && (pointVec.x < 0)) {
            degrees = 180;
        }
        printf("pord esca: %i\n", productoEscalar(newVec,pointVec));
        printf("mod vec 1: %i\n", modulo(newVec));
        printf("mod vec 2: %i\n", modulo(pointVec));
        printf("resultado entero: %i\n", productoEscalar(newVec, pointVec)/(modulo(newVec)*modulo(pointVec)));
        printf("result 1: %f\n", result);

        // acos devuelve el resultado en radianes
        result = acos(result)*180/PI;
        degrees = result;
        if (pointVec.x < 0 && pointVec.y < 0) {
            degrees += 180;
        } else if (pointVec.x < 0 && pointVec.y > 0) {
            degrees = 180 - degrees;
        } else if (pointVec.x > 0 && pointVec.y < 0) {
            degrees = 360 - degrees;
        }
        //printf("grados: %f\n", degrees);
    } else if (pointVec.y > 0) {
        degrees = 90;
    } else {
        degrees = 270;
    }
    return degrees;
}