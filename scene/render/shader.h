#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include "geometry/geometry.hpp"
#include "scene/model/basemodel.h"

using namespace GeometrySpace;

class Shader
{
public:
    Shader();
    Shader(const Matrix<double> &mvpMatrix, const Matrix<double> &modelMatrix,
           const Vector3D<double> &cameraPosition, const Vector3D<double> &lightPosition);
    void setVpMatrix(const Matrix<double> &vpMatrix);
    inline void setModelMatrix(const Matrix<double> &modelMatrix) { modelMatrix_ = modelMatrix; }
    inline void setCameraPosition(const Vector3D<double> &cameraPosition) { cameraPosition_ = cameraPosition; }
    inline void setLightPosition(const Vector3D<double> &lightPosition) { lightPosition_ = lightPosition; }
    inline void setLightColor(const Color &color) { lightColor_ = color; }
    void setMaterial(const Material &material);
    inline Vector3D<double> getCameraPosition() const { return cameraPosition_; }
    inline Vector3D<double> getLightPosition() const { return lightPosition_; }
    inline Matrix<double> getMvpMatrix() const { return mvpMatrix_; }
    inline Matrix<double> getModelMatrix() const { return modelMatrix_; }
    int vertex(std::vector<Vector4D<double>> &result, const std::vector<Vector3D<double>> &triangle, const Vector3D<double> &normal);
    void geometry(const std::vector<Vector4D<double>> &triangle);
    Color fragment(const Vector3D<double> &barycentric, const double &depth) const;
private:
    inline bool pointIsVisible(const Vector4D<double> &plane, const Vector4D<double> &point) const { return (plane * point) > -EPS; }
    void findIntersection(Vector4D<double> &C, const Vector4D<double> &plane, const Vector4D<double> &A, const Vector4D<double> &B) const;
    int clipPolygon(std::vector<Vector4D<double>> &result, const std::vector<Vector4D<double>> &polygon, const Vector4D<double> &plane, const int &length) const;
    Matrix<double> mvpMatrix_;
    Matrix<double> invVpMatrix_;
    Matrix<double> modelMatrix_;
    Vector3D <double> cameraPosition_;
    Vector3D <double> lightPosition_;
    Vector3D<double> normal_;
    std::vector<Vector4D<double>> planes_;
    std::vector<Vector3D<double>> triangle_;
    std::vector<double> w_;
    Color lightColor_;
    Material material_;
};

#endif // SHADER_H
