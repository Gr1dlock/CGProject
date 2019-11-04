#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <vector>
#include "geometry/geometry.hpp"
#include "color/color.h"

struct ModelAttributes
{
    double lengthTop;
    double lengthBot;
    double height;
    int nVerts;
};

using namespace GeometrySpace;

class BaseModel
{
public:
    BaseModel();
    virtual ~BaseModel();
    inline int countVertices() const { return vertices.size(); }
    inline int countTriangles() const { return triangles.size() / 3; }
    void getTriangle(std::vector<Point<3, double>> &triangle, const int &num) const;
    inline MathVector<double> getNormal(const int &index) const { return normals[index]; }
    virtual void changeVerticesCount(const int &verts) = 0;
    virtual void changeTopLength(const double &length) = 0;
    virtual void changeBotLength(const double &length) = 0;
    virtual void changeHeight(const double &height) = 0;
    inline bool isOpaque() const { return fabs(color.getAlpha() - 1) < EPS; }
protected:
    std::vector<Point<3, double>> vertices;
    std::vector<int> triangles;
    std::vector<MathVector<double>> normals;
    virtual void computeVertices(const ModelAttributes &attributes) = 0;
    virtual void computeTriangles(const int &verts) = 0;
    Color color;
    float diffuse;
    float specular;
};

#endif // BASEMODEL_H
