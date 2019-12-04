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

struct ThreadParams
{
    int startRow;
    int endRow;
    int startCol;
    int endCol;
};

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
    void renderTriangle(std::vector<Vector3D<double>> &triangle, const char &objectIndex, const Shader &shader);
    void renderBuffer(ThreadParams params, const std::vector<Vector3D<double>> &triangle, const char &objectIndex, const Shader &shader, const double &square);
    void barycentric(Vector3D<double> &barCoords, const std::vector<Vector3D<double>> &triangle, const QPoint &P, const double &square);
    void viewPort(Vector3D<double> &point);
    int screenWidth;
    int screenHeight;
    std::vector<std::vector<double>> depthBuffer;
    std::vector<std::vector<char>> objectsBuffer;
    QImage *frameBuffer;
};

#endif // RENDERMANAGER_H
