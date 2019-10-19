#ifndef MODEL_H
#define MODEL_H

#include "scene/model/basemodel.h"

class Cube: public BaseModel
{
public:
    Cube(const int &verts, const double &length_top,const double &length_bot, const double &height);
    void changeVerticesCount(const int &verts, const double &length_top,const double &length_bot, const double &height) override;
    void changeTopLength(const double &length) override;
    void changeBotLength(const double &length) override;
    void changeHeight(const double &height) override;
private:
    void computeVertices(const int &verts, const double &length_top,const double &length_bot, const double &height) override;
    void computeTriangles(const int &verts) override;
};

#endif // MODEL_H
