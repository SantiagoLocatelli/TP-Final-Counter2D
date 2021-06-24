#ifndef __GAMEMATH_H__
#define __GAMEMATH_H__

typedef struct coordenada{
    int x, y;
}coordenada_t;

class Math{
    public:
        static double calculateDegrees(coordenada_t center, coordenada_t point);

    private:
};

#endif
