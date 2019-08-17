#ifndef RENDERER_H
#define RENDERER_H

#include <QPainter>
#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class Renderer
{
public:
    Renderer();
    void renderTriangle(QPainter *painter, const Point3D<double> &P0, const Point3D<double> &P1, const Point3D<double> &P2);
private:
    template <typename T>
    double *inerpolate(const T &x0, const T &y0, const T &x1, const T &y1) const;
};

#endif // RENDERER_H
