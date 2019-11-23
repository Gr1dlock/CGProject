#include "shader.h"

Shader::Shader()
    : mvpMatrix_(4, 4),
      modelMatrix_(4, 4),
      lightDir_(3),
      eyeDir_(3)
{
    planes_ = { {-1, 0, 0, 1},
                {1, 0, 0, 1},
                {0, -1, 0, 1},
                {0, 1, 0, 1},
                {0, 0, 1, 1},
                {0, 0, -1, 1}};
}

Shader::Shader(const Matrix<double> &mvpMatrix, const Matrix<double> &modelMatrix,
               const Point<3, double> &cameraPosition, const Point<3, double> &lightPosition)
    : Shader()
{
    mvpMatrix_ = mvpMatrix;
    modelMatrix_ = modelMatrix;
    cameraPosition_ = cameraPosition;
    lightPosition_ = lightPosition;
}

int Shader::vertex(std::vector<Point<4, double>> &result, const std::vector<Point<3, double>> &triangle, const MathVector<double> &normal)
{
    int count = 0;
    normal_ = normal * modelMatrix_;
    if (normal_ * MathVector<double>(triangle[0] * modelMatrix_ - cameraPosition_) < EPS)
    {
        std::vector<Point<4, double>> clippedPolygon(9);
        for (int i = 0; i < 3; i++)
        {
            clippedPolygon[i] = triangle[i];
            clippedPolygon[i] = clippedPolygon[i] * mvpMatrix_;
        }
        count = 3;
        for (int i = 0; i < planes_.size(); i++)
        {
            count = clipPolygon(result, clippedPolygon, planes_[i], count);
            if (count == 0)
                break;
            clippedPolygon = result;
        }
    }
    return count;
}

void Shader::geometry(const std::vector<Point<3, double>> &triangle)
{
    for (const auto &point: triangle)
    {

    }
}

void Shader::findIntersection(Point<4, double> &C, const MathVector<double> &plane, const Point<4, double> &A, const Point<4, double> &B) const
{
    double dA = plane * A;
    double dB = plane * B;
    double t = dA / (dA - dB);
    C = A + (B - A) * t;
}

int Shader::clipPolygon(std::vector<Point<4, double>> &result, const std::vector<Point<4, double>> &polygon, const MathVector<double> &plane, const int &length) const
{
    int first = length - 1;
    int second;
    int count = 0;
    Point<4, double> intersection;
    for (int i = 0; i < length; i++)
    {
        second = i;
        if (pointIsVisible(plane, polygon[second]))
        {
            if (pointIsVisible(plane, polygon[first]))
            {
                result[count] = polygon[second];
                count++;
            }
            else
            {
                findIntersection(intersection, plane, polygon[first], polygon[second]);
                result[count] = intersection;
                count++;
                result[count] = polygon[second];
                count++;
            }
        }
        else
        {
            if (pointIsVisible(plane, polygon[first]))
            {
                findIntersection(intersection, plane, polygon[first], polygon[second]);
                result[count] = intersection;
                count++;
            }
        }
        first = second;
    }
    return count;
}
