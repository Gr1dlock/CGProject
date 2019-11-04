#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <vector>
#include <QImage>
#include "geometry/geometry.hpp"
#include "scene/model/basemodel.h"
#include "scene/light/light.h"

using namespace GeometrySpace;

class RenderManager
{
public:
    RenderManager();
    RenderManager(QImage *frame, const int &sc_width, const int &sc_height);
    void renderModel(const BaseModel &model, const Matrix<double> &viewMatrix, const int &index, const Point<3, double> &cameraPos);
    inline int getIndexByPosition(const int &x, const int &y) const { return objectsBuffer[y][x]; }
    void clearFrame();
private:
    inline bool pointIsVisible(const double &x, const double &y, const double &z) const
    {
        return (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight && z > -1 && z < 1);
    }
    inline bool triangleIsVisible(const std::vector<Point<3, double>> &triangle) const
    {
        return (pointIsVisible(triangle[0].x(), triangle[0].y(), triangle[0].z()) ||
                pointIsVisible(triangle[1].x(), triangle[1].y(), triangle[1].z()) ||
                pointIsVisible(triangle[2].x(), triangle[2].y(), triangle[2].z()));
    }
    void renderTriangle(std::vector<Point<3, double>> &triangle, const Matrix<double> &viewMatrix, const char &objectIndex);
    void barycentric(std::vector<double> &barCoords, const Point<3, double> &A, const Point<3, double> &B, const Point<3, double> &C, const QPoint &P);
    void viewPort(Point<3, double> &point);
    int screenWidth;
    int screenHeight;
    std::vector<std::vector<double>> depthBuffer;
    std::vector<std::vector<char>> objectsBuffer;
    QImage *frameBuffer;
};

#endif // RENDERMANAGER_H
