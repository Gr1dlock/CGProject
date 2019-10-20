#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "scene/model/model.h"

class ModelManager
{
public:
    ModelManager();
    inline int countModels() const { return models.size(); }
    inline Cube getModel(const int &index) const { return models[index]; }
    void addModel(const Cube &model);
    void deleteModel(const int &index);
    void rotateByX(const double &angle, const int &index);
    void rotateByY(const double &angle, const int &index);
    void rotateByZ(const double &angle, const int &index);
    void translateByX(const double &translation, const int &index);
    void translateByY(const double &translation, const int &index);
    void translateByZ(const double &translation, const int &index);
    Matrix<double> getModelView(const int &index);
private:
    std::vector<Cube> models;
    std::vector<Point<3, double>> translations;
    std::vector<Matrix<double>> rotations;
};

#endif // MODELMANAGER_H
