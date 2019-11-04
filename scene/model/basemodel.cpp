#include "basemodel.h"

BaseModel::BaseModel()
{
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
