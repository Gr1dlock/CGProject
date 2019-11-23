#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class Shader
{
public:
    Shader();
    Shader(const Matrix<double> &mvpMatrix, const Matrix<double> &modelMatrix,
           const Point<3, double> &cameraPosition, const Point<3, double> lightPosition);
    inline void setMvpMatrix(const Matrix<double> &mvpMatrix) { mvpMatrix_ = mvpMatrix; }
    inline void setModelMatrix(const Matrix<double> &modelMatrix) { modelMatrix_ = modelMatrix; }
    inline void setCameraPosition(const Point<3, double> &cameraPosition) { cameraPosition_ = cameraPosition; }
    inline void setLightPosition(const Point<3, double> &lightPosition) { lightPosition_ = lightPosition; }
    inline Point<3, double> getCameraPosition() const { return cameraPosition_; }
    inline Point<3, double> getLightPosition() const { return lightPosition_; }
    inline Matrix<double> getMvpMatrix() const { return mvpMatrix_; }
    inline Matrix<double> getModelMatrix() const { return modelMatrix_; }
    int vertex(std::vector<Point<4, double>> &result, const std::vector<Point<3, double>> &triangle, const MathVector<double> &normal) const;
    void geometry(const std::vector<Point<3, double>> &triangle);
private:
    inline bool pointIsVisible(const MathVector<double> &plane, const Point<4, double> &point) const { return (plane * point) > -EPS; }
    void findIntersection(Point<4, double> &C, const MathVector<double> &plane, const Point<4, double> &A, const Point<4, double> &B) const;
    int clipPolygon(std::vector<Point<4, double>> &result, const std::vector<Point<4, double>> &polygon, const MathVector<double> &plane, const int &length) const;
    Matrix<double> mvpMatrix_;
    Matrix<double> modelMatrix_;
    Point <3, double> cameraPosition_;
    Point <3, double> lightPosition_;
    MathVector<double> normal_;
    std::vector<MathVector<double>> planes_;
    std::vector<MathVector<double>> lightDir_;
    std::vector<MathVector<double>> eyeDir_;
};

#endif // SHADER_H
