#include "basemodel.h"


BaseModel::BaseModel()
    : translate(4,4),
      rotate(4,4)
{
    translate.makeIdentity();
    rotate.makeIdentity();
}

BaseModel::~BaseModel()
{
}

void BaseModel::getTriangle(std::vector<Point<3, double> > &triangle, const int &num) const
{
    int index = num * 3;
    triangle[0] = vertices[triangles[index]];
    triangle[1] = vertices[triangles[index + 1]];
    triangle[2] = vertices[triangles[index + 2]];
}

void BaseModel::translateByX(const double &dist)
{
    translate[3][0] += dist;
}

void BaseModel::translateByY(const double &dist)
{
    translate[3][1] += dist;
}

void BaseModel::translateByZ(const double &dist)
{
    translate[3][2] += dist;
}

void BaseModel::rotateByX(const double &angle)
{
    double rad = angle * M_PI / 180;
    Matrix<double> rotateX(4, 4);
    rotateX.makeIdentity();
    rotateX[1][1] = cos(rad);
    rotateX[1][2] = sin(rad);
    rotateX[2][1] = -rotateX[1][2];
    rotateX[2][2] = rotateX[1][1];
    rotate = rotate * rotateX;
}

void BaseModel::rotateByY(const double &angle)
{
    double rad = angle * M_PI / 180;
    Matrix<double> rotateY(4, 4);
    rotateY.makeIdentity();
    rotateY[0][0] = cos(rad);
    rotateY[0][2] = -sin(rad);
    rotateY[2][0] = - rotateY[0][2];
    rotateY[2][2] = rotateY[0][0];
    rotate = rotate * rotateY;
}

void BaseModel::rotateByZ(const double &angle)
{
    double rad = angle * M_PI / 180;
    Matrix<double> rotateZ(4, 4);
    rotateZ.makeIdentity();
    rotateZ[0][0] = cos(rad);
    rotateZ[0][1] = sin(rad);
    rotateZ[1][0] = -rotateZ[0][1];
    rotateZ[1][1] = rotateZ[0][0];
    rotate = rotate * rotateZ;
}

void BaseModel::changeModel(const int &verts, const double &length_top,const double &length_bot, const double &height)
{
    vertices.clear();
    triangles.clear();
    computeVertices(verts, length_top, length_bot, height);
    computeTriangles(verts);
}
