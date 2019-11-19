#include "basemodel.h"

BaseModel::BaseModel()
    :rotation_(4, 4),
      translation_(0, 0, 0)
{
    rotation_.makeIdentity();
}

BaseModel::~BaseModel()
{
}

void BaseModel::getTriangle(std::vector<Point<3, double> > &triangle, const int &num) const
{
    int index = num * 3;
    triangle[0] = vertices_[triangles_[index]];
    triangle[1] = vertices_[triangles_[index + 1]];
    triangle[2] = vertices_[triangles_[index + 2]];
}


