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

        static float degreesToRadians(float degrees);
        static float radiansToDegrees(float radians);
        static float calculateRadians(coordenada_t center, coordenada_t point);
        static int ruleOfThree(float x_f, float total_f, int total_i);

    private:
};

#endif
