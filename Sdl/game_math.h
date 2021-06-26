#ifndef __GAMEMATH_H__
#define __GAMEMATH_H__

typedef struct coordenada{
    int x, y;
}coordenada_t;

class Math{
    public:
        /**
         * calcula los grados entre el vector point y la proyeccion del vector point 
         * en el eje x.
         */
        static double calculateDegrees(coordenada_t center, coordenada_t point);

    private:
};

#endif
