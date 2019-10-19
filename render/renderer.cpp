#include "renderer.h"
#include <QDebug>

Renderer::Renderer()
{
}

void Renderer::renderTriangle(QPainter *painter, std::vector<Point<3, double>> &triangle)
{
    Matrix<double> MVP(camera.lookAt() * perspective.perspectiveProjection());
    for (int i = 0; i < 3; i++)
    {
        Point<4, double> tmp(triangle[i]);
        tmp = tmp * MVP;
        triangle[i] = tmp;
        view_port.toScreen(triangle[i]);
    }
    Point<2, double> left_corner(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Point<2, double> right_corner(0, 0);
    for (int i = 0; i < 3; i++)
    {
        right_corner.setX(qMax(right_corner.x(), triangle[i].x()));
        right_corner.setY(qMax(right_corner.y(), triangle[i].y()));
        left_corner.setX(qMin(left_corner.x(), triangle[i].x()));
        left_corner.setY(qMin(left_corner.y(), triangle[i].y()));
    }
    for (double i = left_corner.x(); i <= right_corner.x(); i++)
    {
        for (double j = left_corner.y(); j <= right_corner.y(); j++)
        {
            Point<3, double> bar_coords = barycentric(triangle, Point<2, double>(i, j));
            if (bar_coords.x() >= -EPS && bar_coords.y() >= -EPS && bar_coords.z() >= -EPS)
            {
                painter->drawPoint(static_cast<int>(i), static_cast<int>(j));
            }
        }
    }
    painter->setPen(Qt::black);
    painter->drawLine(QPoint(triangle[0].x(), triangle[0].y()), QPoint(triangle[1].x(), triangle[1].y()));
    painter->drawLine(QPoint(triangle[1].x(), triangle[1].y()), QPoint(triangle[2].x(), triangle[2].y()));
    painter->drawLine(QPoint(triangle[0].x(), triangle[0].y()), QPoint(triangle[2].x(), triangle[2].y()));
    painter->setPen(Qt::red);
}

Point<3, double> Renderer::barycentric(const std::vector<Point<3, double>> &triangle, const Point<2, double> &P)
{
    Point<3, double> A = triangle[0];
    Point<3, double> B = triangle[1];
    Point<3, double> C = triangle[2];
    double square = (A.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - A.x());
    if (square > EPS)
    {
        Point<3, double> bar_coords;
        bar_coords[0] = (P.y() - C.y()) * (B.x() - C.x()) + (B.y() - C.y()) * (C.x() - P.x());
        bar_coords[0] /= square;
        bar_coords[1] = (P.y() - A.y()) * (C.x() - A.x()) + (C.y() - A.y()) * (A.x() - P.x());
        bar_coords[1] /= square;
        bar_coords[2] = 1 - bar_coords[0] - bar_coords[1];
        return bar_coords;
    }
    return Point<3, double> (-1, -1, -1);
}

