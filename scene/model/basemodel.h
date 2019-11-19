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
    inline int countVertices() const { return vertices_.size(); }
    inline int countTriangles() const { return triangles_.size() / 3; }
    inline Point<3, double> getTranslation() const { return translation_; }
    inline Matrix<double> getRotation() const { return rotation_; }
    inline void setTranslation(const Point<3, double> &translation) { translation_ = translation; }
    inline void setRotation(const Matrix<double> &rotation) { rotation_ = rotation; }
    void getTriangle(std::vector<Point<3, double>> &triangle, const int &num) const;
    inline MathVector<double> getNormal(const int &index) const { return normals_[index]; }
    virtual void changeVerticesCount(const int &verts) = 0;
    virtual void changeTopLength(const double &length) = 0;
    virtual void changeBotLength(const double &length) = 0;
    virtual void changeHeight(const double &height) = 0;
protected:
    virtual void computeVertices(const ModelAttributes &attributes) = 0;
    virtual void computeTriangles(const int &verts) = 0;
    virtual void computeNormals(const int &verts) = 0;
    virtual ModelAttributes getAttributes() const = 0 ;
    std::vector<Point<3, double>> vertices_;
    std::vector<int> triangles_;
    std::vector<MathVector<double>> normals_;
    Matrix<double> rotation_;
    Point<3, double> translation_;
};

#endif // BASEMODEL_H
