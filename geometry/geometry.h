#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <stdexcept>

#define EPS 1E-5

namespace GeometrySpace
{
    template<typename T>
    class MathVector;

    template<int size, typename T>
    class Point;

    template<typename T>
    class Matrix;
}
#endif // GEOMETRY_H
