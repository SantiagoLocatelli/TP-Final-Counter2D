#ifndef __GAMEMATH_H__
#define __GAMEMATH_H__

#include "../LevelInfo.h"

class Math{
    public:

        static int manhattanDistance(Coordinate point1, Coordinate point2);
        static float degreesToRadians(float degrees);
        static float radiansToDegrees(float radians);
        static float calculateRadians(Coordinate center, Coordinate point);
        static int metersToPixels(float x_f, float total_f, int total_i);
        static float pixelsToMeters(int pixels, int totalPixels, float totalMeters);
        static int senoOppHyp(float radians, int hypotenuse);
        static int cosAdHyp(float radians, int hypotenuse);
        static int getRandomNumberBetween(int min, int max);
        static bool equalCoords(Coordinate coord1, Coordinate coord2);
        static int pythagoras(int cat1, int cat2);

    private:
};

#endif
