#ifndef LIGHT_H
#define LIGHT_H

#include "color/color.h"
#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class Light
{
public:
    Light();
private:
    Point<3, double> position;
    Color color;
};

#endif // LIGHT_H
