#ifndef MODEL_H
#define MODEL_H

#include "basemodel.h"

class Cube: public BaseModel
{
public:
    Cube(const int &verts, const double &length_top,const double &length_bot, const double &height);
private:
    void computeVertices(const int &verts, const double &length_top,const double &length_bot, const double &height) override;
    void computeTriangles(const int &verts) override;
};

#endif // MODEL_H
