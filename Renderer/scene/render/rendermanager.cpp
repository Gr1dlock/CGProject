#include "rendermanager.h"

#include <QtDebug>

RenderManager::RenderManager()
{
}

RenderManager::RenderManager(QImage *frame, const int &sc_width, const int &sc_height)
    : screenWidth(sc_width),
      screenHeight(sc_height),
      frameBuffer(frame)
{
    depthBuffer = std::vector<std::vector<double>> (screenHeight, std::vector<double>(screenWidth, 2));
    objectsBuffer = std::vector<std::vector<char>> (screenHeight, std::vector<char>(screenWidth, -1));
    frameBuffer->fill(Qt::black);
}

void RenderManager::renderModel(const BaseModel &model, const Matrix<double> &viewMatrix, const int &index, const Point<3, double> &cameraPos)
{
    std::vector<Point<3, double>> triangle(3);
    for (int j = 0; j < model.countTriangles(); j++)
    {
        model.getTriangle(triangle, j);
        if (model.getNormal(j) * MathVector<double>(triangle[0] - cameraPos) < 0)
        {
            renderTriangle(triangle, viewMatrix, static_cast<char>(index));
        }
    }
}

void RenderManager::clearFrame()
{
    frameBuffer->fill(Qt::black);
    depthBuffer.clear();
    objectsBuffer.clear();
    depthBuffer = std::vector<std::vector<double>> (screenHeight, std::vector<double>(screenWidth, 1));
    objectsBuffer = std::vector<std::vector<char>> (screenHeight, std::vector<char>(screenWidth, -1));
}

void RenderManager::renderTriangle(std::vector<Point<3, double>> &triangle, const Matrix<double> &viewMatrix, const char &objectIndex)
{
    for (int i = 0; i < 3; i++)
    {
        Point<4, double> tmp(triangle[i]);
        tmp = tmp * viewMatrix;
        triangle[i] = tmp;
        viewPort(triangle[i]);
    }
    if (triangleIsVisible(triangle))
    {
        Point<2, int> leftCorner(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
        Point<2, int> rightCorner(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
        for (int i = 0; i < 3; i++)
        {
            rightCorner.setX(std::max(rightCorner.x(), static_cast<int>(triangle[i].x())));
            rightCorner.setY(std::max(rightCorner.y(),static_cast<int>(triangle[i].y())));
            leftCorner.setX(std::min(leftCorner.x(), static_cast<int>(triangle[i].x())));
            leftCorner.setY(std::min(leftCorner.y(), static_cast<int>(triangle[i].y())));
        }
        rightCorner.setX(std::min(rightCorner.x(), screenWidth - 1));
        rightCorner.setY(std::min(rightCorner.y(),screenHeight - 1));
        leftCorner.setX(std::max(leftCorner.x(), 0));
        leftCorner.setY(std::max(leftCorner.y(), 0));
        triangle[0].setZ(1 / triangle[0].z());
        triangle[1].setZ(1 / triangle[1].z());
        triangle[2].setZ(1 / triangle[2].z());
        for (int i = leftCorner.x(); i <= rightCorner.x(); i++)
        {
            for (int j = leftCorner.y(); j <= rightCorner.y(); j++)
            {
                std::vector<double> barCoords = barycentric(triangle, Point<2, double>(i, j));
                if (barCoords[0] >= -EPS && barCoords[1] >= -EPS && barCoords[2] >= -EPS)
                {
                    double z = 1 / (barCoords[0] * triangle[0].z() + barCoords[1] * triangle[1].z() + barCoords[2] * triangle[2].z());
                    if (z < depthBuffer[j][i] && z > -1 && z < 1)
                    {
                        depthBuffer[j][i] = z;
                        objectsBuffer[j][i] = objectIndex;
                        frameBuffer->setPixel(i, j, qRgb(255, 0, 0));
                    }
                }
            }
        }
    }
}

void RenderManager::viewPort(Point<3, double> &point)
{
    point.setX(round((point.x() + 1) * 0.5 * screenWidth));
    point.setY(round((point.y() + 1) * 0.5 * screenHeight));
}


std::vector<double> RenderManager::barycentric(const std::vector<Point<3, double>> &triangle, const Point<2, double> &P)
{
    Point<3, double> A = triangle[0];
    Point<3, double> B = triangle[1];
    Point<3, double> C = triangle[2];
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
    if (square > EPS)
    {
        std::vector<double> barCoords(3);
        barCoords[0] = (P.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - P.x());
        barCoords[0] /= square;
        barCoords[1] = (P.y() - A.y()) * (C.x() - A.x()) + (C.y() - A.y()) * (A.x() - P.x());
        barCoords[1] /= square;
        barCoords[2] = 1 - barCoords[0] - barCoords[1];
        return barCoords;
    }
    return std::vector<double> {-1, -1, -1};
}
