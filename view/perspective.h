#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class Perspective
{
public:
    Perspective();
    Perspective(const double &fov, const double &near, const double &far, const double &ratio);
    Matrix<double> perspectiveProjection();
private:
    double field_of_view;
    double near_plane;
    double far_plane;
    double aspect_ratio;
};

#endif // PERSPECTIVE_H
