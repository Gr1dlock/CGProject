#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <vector>
#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class BaseModel
{
public:
    BaseModel();
    virtual ~BaseModel();
    inline int countVertices() const { return vertices.size(); }
    inline int countTriangles() const { return triangles.size() / 3; }
    void getTriangle(std::vector<Point<3, double>> &triangle, const int &num) const;
    void translateByX(const double &dist);
    void translateByY(const double &dist);
    void translateByZ(const double &dist);
    void rotateByX(const double &angle);
    void rotateByY(const double &angle);
    void rotateByZ(const double &angle);
    inline Matrix<double> getMatrix() const { return rotate * translate; }
    void changeModel(const int &verts, const double &length_top,const double &length_bot, const double &height);
protected:
    std::vector<Point<3, double>> vertices;
    std::vector<int> triangles;
    Matrix<double> translate;
    Matrix<double> rotate;
    virtual void computeVertices(const int &verts, const double &length_top,const double &length_bot, const double &height) = 0;
    virtual void computeTriangles(const int &verts) = 0;
};

#endif // BASEMODEL_H
