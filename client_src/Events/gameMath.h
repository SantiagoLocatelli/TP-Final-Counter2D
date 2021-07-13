#ifndef __GAMEMATH_H__
#define __GAMEMATH_H__

#include "../levelInfo.h"

class Math{
    public:

        static int manhattanDistance(Coordinate point1, Coordinate point2);
        static float degreesToRadians(float degrees);
        static float radiansToDegrees(float radians);
        static float calculateRadians(Coordinate center, Coordinate point);
        static int ruleOfThree(float x_f, float total_f, int total_i);
        static int senoOppHyp(float radians, int hypotenuse);
        static int cosOppHyp(float radians, int hypotenuse);

    private:
};

#endif
