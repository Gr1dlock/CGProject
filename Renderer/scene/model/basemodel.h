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
    virtual void changeVerticesCount(const int &verts, const double &length_top,const double &length_bot, const double &height) = 0;
    virtual void changeTopLength(const double &length) = 0;
    virtual void changeBotLength(const double &length) = 0;
    virtual void changeHeight(const double &height) = 0;

protected:
    std::vector<Point<3, double>> vertices;
    std::vector<int> triangles;
    virtual void computeVertices(const int &verts, const double &length_top,const double &length_bot, const double &height) = 0;
    virtual void computeTriangles(const int &verts) = 0;
};

#endif // BASEMODEL_H
