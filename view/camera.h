#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class Camera
{
public:
    Camera();
    Camera(const Point<3, double> &eye, const Point<3, double> &center, const MathVector<double> &top);
    Matrix<double> lookAt();
private:
    Point<3, double> position;
    MathVector<double> direction;
    MathVector<double> up;
    MathVector<double> right;
};

#endif // CAMERA_H
