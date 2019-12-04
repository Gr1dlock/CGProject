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

void RenderManager::renderModel(const BaseModel &model, Shader &shader, const int &index)
{
    char objectIndex = index;
    std::vector<Vector3D<double>> triangle(3);
    std::vector<Vector4D<double>> result(9);
    int count;
//    double renderTime = 0;
//    for (int k = 0; k < 100; k++)
//    {
//        clearFrame();
//        auto time1 = std::chrono::steady_clock::now();
        for (int j = 0; j < model.countTriangles(); j++)
        {
            model.getTriangle(triangle, j);
            count = shader.vertex(result, triangle, model.getNormal(j));
            for (int i = 0; i < count - 2; i++)
            {
                shader.geometry({result[i+2], result[i+1], result[0]});
                triangle[2] = result[0];
                triangle[1] = result[i + 1];
                triangle[0] = result[i + 2];
                renderTriangle(triangle, objectIndex, shader);
            }
        }
//        auto time2 = std::chrono::steady_clock::now();
//        renderTime += std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000.0;
//    }
//    qDebug() << "Render time: " << renderTime / 100;
}

void RenderManager::clearFrame()
{
    frameBuffer->fill(Qt::black);
    depthBuffer = std::vector<std::vector<double>> (screenHeight, std::vector<double>(screenWidth, 2));
    objectsBuffer = std::vector<std::vector<char>> (screenHeight, std::vector<char>(screenWidth, -1));
}

void RenderManager::renderTriangle(std::vector<Vector3D<double>> &triangle, const char &objectIndex, const Shader &shader)
{
    for (auto &point: triangle)
    {
        viewPort(point);
        point.setZ(1 / point.z());
    }
    QPoint leftCorner(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    QPoint rightCorner(0, 0);
    for (const auto &point: triangle)
    {
        rightCorner.setX(std::max(rightCorner.x(), static_cast<int>(point.x())));
        rightCorner.setY(std::max(rightCorner.y(),static_cast<int>(point.y())));
        leftCorner.setX(std::min(leftCorner.x(), static_cast<int>(point.x())));
        leftCorner.setY(std::min(leftCorner.y(), static_cast<int>(point.y())));
    }
    rightCorner.setX(std::min(rightCorner.x(), screenWidth - 1));
    rightCorner.setY(std::min(rightCorner.y(),screenHeight - 1));
    double square = (triangle[0].y() - triangle[2].y()) * (triangle[1].x() - triangle[2].x()) +
            (triangle[1].y() - triangle[2].y()) * (triangle[2].x() - triangle[0].x());
    std::vector<std::thread> threads(8);
    ThreadParams params;
    params.startRow = leftCorner.y();
    params.endRow = rightCorner.y();
    double start = leftCorner.x();
    double step = (rightCorner.x() - leftCorner.x()) / 8.0;
    for (auto &thread: threads)
    {
        params.startCol = round(start);
        params.endCol = round(start + step);
        thread = std::thread(&RenderManager::renderBuffer, this, params, std::cref(triangle), std::cref(objectIndex), std::cref(shader), std::cref(square));
        start += step;
    }
    for (auto &thread:threads)
    {
        thread.join();
    }
}

void RenderManager::renderBuffer(ThreadParams params, const std::vector<Vector3D<double> > &triangle, const char &objectIndex, const Shader &shader, const double &square)
{
    Vector3D<double> barCoords;
    double z;
    Color color;
    for (int i = params.startCol; i <= params.endCol; i++)
    {
        for (int j = params.startRow; j <= params.endRow; j++)
        {
            barycentric(barCoords, triangle, QPoint(i, j), square);
            if (barCoords.x() >= -EPS && barCoords.y() >= -EPS && barCoords.z() >= -EPS)
            {
                z = 1 / (barCoords.x() * triangle[0].z() + barCoords.y() * triangle[1].z() + barCoords.z() * triangle[2].z());
                if (z <= depthBuffer[j][i])
                {
                    depthBuffer[j][i] = z;
                    objectsBuffer[j][i] = objectIndex;
                    color = shader.fragment(barCoords, z);
                    frameBuffer->setPixel(i, j, color.rgb());
                }
            }
        }
    }
}

void RenderManager::viewPort(Vector3D<double> &point)
{
    point.setX((point.x() + 1) * 0.5 * screenWidth);
    point.setY(screenHeight - (point.y() + 1) * 0.5 * screenHeight);
    point.setZ((point.z() + 2) * 0.5);
}

void RenderManager::barycentric(Vector3D<double> &barCoords, const std::vector<Vector3D<double>> &triangle, const QPoint &P, const double &square)
{
    barCoords.setX(((P.y() - triangle[2].y()) * (triangle[1].x() - triangle[2].x()) + (triangle[1].y() - triangle[2].y()) * (triangle[2].x() - P.x())) / square);
    barCoords.setY(((P.y() - triangle[0].y()) * (triangle[2].x() - triangle[0].x()) + (triangle[2].y() - triangle[0].y()) * (triangle[0].x() - P.x())) / square);
    barCoords.setZ(1 - barCoords.x() - barCoords.y());
}
