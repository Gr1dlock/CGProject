#include "rendermanager.h"

RenderManager::RenderManager()
{
}

RenderManager::RenderManager(QImage *frame, const int &sc_width, const int &sc_height)
    : screen_width(sc_width),
      screen_height(sc_height),
      frame_buffer(frame)
{
    depth_buffer = std::vector<std::vector<double>> (screen_height, std::vector<double>(screen_width, 2));
    frame_buffer->fill(Qt::black);
}

void RenderManager::renderTriangle(std::vector<Point<3, double>> &triangle, const Matrix<double> &Mpersp)
{
    for (int i = 0; i < 3; i++)
    {
        Point<4, double> tmp(triangle[i]);
        tmp = tmp * Mpersp;
        triangle[i] = tmp;
        viewPort(triangle[i]);
    }
    Point<2, double> left_corner(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Point<2, double> right_corner(0, 0);
    for (int i = 0; i < 3; i++)
    {
        right_corner.setX(std::max(right_corner.x(), triangle[i].x()));
        right_corner.setY(std::max(right_corner.y(), triangle[i].y()));
        left_corner.setX(std::min(left_corner.x(), triangle[i].x()));
        left_corner.setY(std::min(left_corner.y(), triangle[i].y()));
    }
    triangle[0].setZ(1 / triangle[0].z());
    triangle[1].setZ(1 / triangle[1].z());
    triangle[2].setZ(1 / triangle[2].z());
    for (double i = left_corner.x(); i <= right_corner.x(); i++)
    {
        for (double j = left_corner.y(); j <= right_corner.y(); j++)
        {
            std::vector<double> bar_coords = barycentric(triangle, Point<2, double>(i, j));
            if (bar_coords[0] >= -EPS && bar_coords[1] >= -EPS && bar_coords[2] >= -EPS)
            {
                double z = 1 / (bar_coords[0] * triangle[0].z() + bar_coords[1] * triangle[1].z() + bar_coords[2] * triangle[2].z());
                if (z < depth_buffer[static_cast<int>(i)][static_cast<int>(j)])
                {
                    depth_buffer[static_cast<int>(i)][static_cast<int>(j)] = z;
                    frame_buffer->setPixel(static_cast<int>(i), static_cast<int>(j), qRgb(255, 0, 0));
                }
            }
        }
    }
}

void RenderManager::viewPort(Point<3, double> &point)
{
    point.setX(round((point.x() + 1) * 0.5 * screen_width));
    point.setY(round(screen_height - (point.y() + 1) * 0.5 * screen_height));
}

std::vector<double> RenderManager::barycentric(const std::vector<Point<3, double>> &triangle, const Point<2, double> &P)
{
    Point<3, double> A = triangle[0];
    Point<3, double> B = triangle[1];
    Point<3, double> C = triangle[2];
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
    if (square > EPS)
    {
        std::vector<double> bar_coords(3);
        bar_coords[0] = (P.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - P.x());
        bar_coords[0] /= square;
        bar_coords[1] = (P.y() - A.y()) * (C.x() - A.x()) + (C.y() - A.y()) * (A.x() - P.x());
        bar_coords[1] /= square;
        bar_coords[2] = 1 - bar_coords[0] - bar_coords[1];
        return bar_coords;
    }
    return std::vector<double> {-1, -1, -1};
}
