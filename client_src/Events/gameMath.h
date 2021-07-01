#ifndef __GAMEMATH_H__
#define __GAMEMATH_H__

typedef struct coordenada{
    int x, y;
}coordenada_t;

class Math{
    public:

        static int manhattanDistance(coordenada_t point1, coordenada_t point2);

        /**
         * calcula los grados entre el vector point y la proyeccion del vector point 
         * en el eje x.
         */
        static float calculateDegrees(coordenada_t center, coordenada_t point);

        static float degreesToRadians(float degrees);
        static float radiansToDegrees(float radians);

    private:
};

#endif
