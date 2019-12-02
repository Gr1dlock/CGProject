#include "shader.h"
#include <QtDebug>
Shader::Shader()
    : mvpMatrix_(4, 4),
      invVpMatrix_(4, 4),
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

Shader::Shader(const Matrix<double> &vpMatrix, const Matrix<double> &modelMatrix,
               const Vector3D<double> &cameraPosition, const Vector3D<double> &lightPosition)
    : Shader()
{
    mvpMatrix_ = modelMatrix * vpMatrix;
    modelMatrix_ = modelMatrix;
    invVpMatrix_ = vpMatrix;
    invVpMatrix_.inverse();
    cameraPosition_ = cameraPosition;
    lightPosition_ = lightPosition;
}

void Shader::setVpMatrix(const Matrix<double> &vpMatrix)
{
    mvpMatrix_ = modelMatrix_ * vpMatrix;
    invVpMatrix_ = vpMatrix;
    invVpMatrix_.inverse();
}

void Shader::setMaterial(const Material &material)
{
    material_.diffuse_ = material.diffuse_;
    material_.specular_ = material.specular_;
    material_.shininess_ = material.shininess_;
}

int Shader::vertex(std::vector<Vector4D<double>> &result, const std::vector<Vector3D<double>> &triangle, const Vector3D<double> &normal)
{
    int count = 0;
    normal_ = normal * modelMatrix_;
    if (normal_ * ((triangle[0] ^ modelMatrix_) - cameraPosition_) < EPS)
    {
        std::vector<Vector4D<double>> clippedPolygon(9);
        for (int i = 0; i < 3; i++)
        {
            clippedPolygon[i] = triangle[i];
            clippedPolygon[i].setW(1);
            clippedPolygon[i] = clippedPolygon[i] * mvpMatrix_;
        }
        count = 3;
        for (int i = 0; i < planes_.size(); i++)
        {
            count = clipPolygon(result, clippedPolygon, planes_[i], count);
            if (count == 0) break;
            clippedPolygon = result;
        }
    }
    return count;
}

void Shader::geometry(const std::vector<Vector4D<double>> &triangle)
{
    Vector3D<double> point;
    for (int i = 0; i < 3; i++)
    {
        point = triangle[i] * invVpMatrix_;
        lightDir_[i] = lightPosition_ - point;
        lightDir_[i].normalize();
        eyeDir_[i] = cameraPosition_ - point;
        eyeDir_[i].normalize();
    }
}

Color Shader::fragment(const std::vector<double> &barycentric) const
{
    Vector3D<double> lightDir(lightDir_[2] * barycentric[2] + lightDir_[1] * barycentric[1] + lightDir_[0] * barycentric[0]);
    Vector3D<double> eyeDir(eyeDir_[2] * barycentric[2] + eyeDir_[1] * barycentric[1] + eyeDir_[0] * barycentric[0]);
    lightDir.normalize();
    eyeDir.normalize();
    Vector3D<double> halfWay(lightDir + eyeDir);
    halfWay.normalize();
    double specComponent = std::pow(std::max(normal_ * halfWay, 0.0), material_.shininess_);
    double diffComponent = std::max(normal_ * lightDir, 0.0);
    double ambient = 0.1;
    return lightColor_ * (material_.specular_ * specComponent + material_.diffuse_ * diffComponent) +  material_.diffuse_ * ambient;
}

void Shader::findIntersection(Vector4D<double> &C, const Vector4D<double> &plane, const Vector4D<double> &A, const Vector4D<double> &B) const
{
    double dA = plane * A;
    double dB = plane * B;
    double t = dA / (dA - dB);
    C = A + (B - A) * t;
}

int Shader::clipPolygon(std::vector<Vector4D<double>> &result, const std::vector<Vector4D<double>> &polygon, const Vector4D<double> &plane, const int &length) const
{
    int first = length - 1;
    int second;
    int count = 0;
    Vector4D<double> intersection;
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
