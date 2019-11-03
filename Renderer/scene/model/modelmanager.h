#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <variant>
#include "scene/model/model.h"

struct ModelMovement
{
    double angleX;
    double angleY;
    double angleZ;
    double dx;
    double dy;
    double dz;
};

using ModelTransformation = std::variant<ModelAttributes, ModelMovement>;

class ModelManager
{
public:
    ModelManager();
    inline int countModels() const { return models.size(); }
    inline Cube getModel(const int &index) const { return models[index]; }
    void addModel(const Cube &model);
    void deleteModel(const int &index);
    void transformModel(const ModelTransformation &transformation, const int &index);
    void rotateByX(const double &angle, const int &index);
    void rotateByY(const double &angle, const int &index);
    void rotateByZ(const double &angle, const int &index);
    inline void translateByX(const double &translation, const int &index) { translations[index] += Point<3, double>(translation, 0, 0); }
    inline void translateByY(const double &translation, const int &index) { translations[index] += Point<3, double>(0, translation, 0); }
    inline void translateByZ(const double &translation, const int &index) { translations[index] += Point<3, double>(0, 0, translation); }
    Matrix<double> getModelView(const int &index) const;
private:
    std::vector<Cube> models;
    std::vector<Point<3, double>> translations;
    std::vector<Matrix<double>> rotations;
};

#endif // MODELMANAGER_H
