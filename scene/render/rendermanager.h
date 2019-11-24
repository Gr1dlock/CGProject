#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <vector>
#include <QImage>
#include <QtDebug>
#include <chrono>
#include <thread>
#include "geometry/geometry.hpp"
#include "scene/model/basemodel.h"
#include "scene/light/light.h"
#include "scene/render/shader.h"

using namespace GeometrySpace;

class RenderManager
{
public:
    RenderManager();
    RenderManager(QImage *frame, const int &sc_width, const int &sc_height);
    void renderModel(const BaseModel &model, Shader &shader, const int &index);
    inline int getIndexByPosition(const int &x, const int &y) const { return static_cast<int>(objectsBuffer[y][x]); }
    void clearFrame();
private:
    void renderTriangle(std::vector<Point<3, double>> &triangle, const char &objectIndex, const Shader &shader);
    void barycentric(std::vector<double> &barCoords, const std::vector<Point<3, double>> &triangle, const QPoint &P, const double &square);
    void viewPort(Point<3, double> &point);
    int screenWidth;
    int screenHeight;
    std::vector<std::vector<double>> depthBuffer;
    std::vector<std::vector<char>> objectsBuffer;
    QImage *frameBuffer;
};

#endif // RENDERMANAGER_H
