#include "rendermanager.h"

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

void RenderManager::renderModel(const BaseModel &model, const Shader &shader, const int &index)
{
    double renderTime = 0;
    std::vector<Point<3, double>> triangle(3);
    std::vector<Point<4, double>> result(9);
    int count;
    for (int k = 0; k < 100; k++)
    {
        clearFrame();
        for (int j = 0; j < model.countTriangles(); j++)
        {
            model.getTriangle(triangle, j);
            count = shader.vertex(result, triangle, model.getNormal(j));
            for (int i = 0; i < count - 2; i++)
            {
                triangle[2] = result[0];
                triangle[1] = result[i + 1];
                triangle[0] = result[i + 2];
                auto time1 = std::chrono::steady_clock::now();
                renderTriangle(triangle, static_cast<char>(index));
                auto time2 = std::chrono::steady_clock::now();
                renderTime += std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000.0;
            }
        }
    }
    qDebug() << "Render time: " << renderTime / 100;
}

void RenderManager::clearFrame()
{
    frameBuffer->fill(Qt::black);
    depthBuffer = std::vector<std::vector<double>> (screenHeight, std::vector<double>(screenWidth, 2));
    objectsBuffer = std::vector<std::vector<char>> (screenHeight, std::vector<char>(screenWidth, -1));
}

void RenderManager::renderTriangle(std::vector<Point<3, double>> &triangle, const char &objectIndex)
{
    for (int i = 0; i < 3; i++)
    {
        viewPort(triangle[i]);
    }
    QPoint leftCorner(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    QPoint rightCorner(0, 0);
    for (int i = 0; i < 3; i++)
    {
        rightCorner.setX(std::max(rightCorner.x(), static_cast<int>(triangle[i].x())));
        rightCorner.setY(std::max(rightCorner.y(),static_cast<int>(triangle[i].y())));
        leftCorner.setX(std::min(leftCorner.x(), static_cast<int>(triangle[i].x())));
        leftCorner.setY(std::min(leftCorner.y(), static_cast<int>(triangle[i].y())));
    }
    rightCorner.setX(std::min(rightCorner.x(), screenWidth - 1));
    rightCorner.setY(std::min(rightCorner.y(),screenHeight - 1));
    double square = (triangle[0].y() - triangle[2].y()) * (triangle[1].x() - triangle[2].x()) + (triangle[1].y() - triangle[2].y()) * (triangle[2].x() - triangle[0].x());
    triangle[0].setZ(1 / triangle[0].z());
    triangle[1].setZ(1 / triangle[1].z());
    triangle[2].setZ(1 / triangle[2].z());
    std::vector<double> barCoords(3);
    for (int i = leftCorner.x(); i <= rightCorner.x(); i++)
    {
        for (int j = leftCorner.y(); j <= rightCorner.y(); j++)
        {
            barycentric(barCoords, triangle, QPoint(i, j), square);
            if (barCoords[0] >= -EPS && barCoords[1] >= -EPS && barCoords[2] >= -EPS)
            {
                double z = 1 / (barCoords[0] * triangle[0].z() + barCoords[1] * triangle[1].z() + barCoords[2] * triangle[2].z());
                if (z <= depthBuffer[j][i])
                {
                    depthBuffer[j][i] = z;
                    objectsBuffer[j][i] = objectIndex;
                    if (objectIndex == 0)
                        frameBuffer->setPixel(i, j, qRgb(255, 0, 0));
                    else
                        frameBuffer->setPixel(i, j, qRgb(0, 255, 0));
                }
            }
        }

    }
}

void RenderManager::viewPort(Point<3, double> &point)
{
    point.setX((point.x() + 1) * 0.5 * screenWidth);
    point.setY(screenHeight - (point.y() + 1) * 0.5 * screenHeight);
    point.setZ((point.z() + 1) * 0.5);
}

void RenderManager::barycentric(std::vector<double> &barCoords, const std::vector<Point<3, double>> &triangle, const QPoint &P, const double &square)
{
    if (square > -EPS)
    {
        barCoords[0] = (P.y() - triangle[2].y()) * (triangle[1].x() - triangle[2].x()) + (triangle[1].y() - triangle[2].y()) * (triangle[2].x() - P.x());
        barCoords[0] /= square;
        barCoords[1] = (P.y() - triangle[0].y()) * (triangle[2].x() - triangle[0].x()) + (triangle[2].y() - triangle[0].y()) * (triangle[0].x() - P.x());
        barCoords[1] /= square;
        barCoords[2] = 1 - barCoords[0] - barCoords[1];
    }
    else
    {
        barCoords[0] = -1;
    }
}
