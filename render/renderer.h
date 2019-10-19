#ifndef RENDERER_H
#define RENDERER_H

#include <QPainter>
#include "view/viewport.h"
#include "view/camera.h"
#include "view/perspective.h"

using namespace GeometrySpace;

class Renderer
{
public:
    Renderer();
    inline void setView(const int &screen_width, const int &screen_height) { view_port = ViewPort(screen_width, screen_height); }
    inline void setCamera(const Point<3, double> &eye, const Point<3, double> &center, const MathVector<double> &top) { camera = Camera(eye, center, top); }
    inline void setPerspective(const double &fov, const double &near, const double &far, const double &ratio) { perspective = Perspective(fov, near, far, ratio); }
    void renderTriangle(QPainter *painter, std::vector<Point<3, double>> &triangle);
private:
    Point<3, double> barycentric(const std::vector<Point<3, double>> &triangle, const Point<2, double> &P);
    ViewPort view_port;
    Camera camera;
    Perspective perspective;
    std::vector<std::vector<double>> depth_buffer;
};

#endif // RENDERER_H
