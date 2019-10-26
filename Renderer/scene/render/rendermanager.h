#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <vector>
#include <QImage>
#include "geometry/geometry.hpp"
#include "scene/light/light.h"

using namespace GeometrySpace;

class RenderManager
{
public:
    RenderManager();
    RenderManager(QImage *frame, const int &sc_width, const int &sc_height);
    void renderTriangle(std::vector<Point<3, double>> &triangle, const Matrix<double> &Mpersp);
    void renderFrame(const QPainter *painter);

private:
    int screen_width;
    int screen_height;
    std::vector<std::vector<double>> depth_buffer;
    QImage *frame_buffer;
    std::vector<double> barycentric(const std::vector<Point<3, double>> &triangle, const Point<2, double> &P);
    void viewPort(Point<3, double> &point);
};

#endif // RENDERMANAGER_H
