#include "modelmanager.h"

#include <QtDebug>

ModelManager::ModelManager()
{

}

void ModelManager::addModel(const Cube &model)
{
    models.push_back(model);
    translations.emplace_back(0, 0, 0);
    Matrix<double> rotation(4, 4);
    rotation.makeIdentity();
    rotations.push_back(rotation);
}

void ModelManager::deleteModel(const int &index)
{
    models.erase(models.begin() + index);
    translations.erase(translations.begin() + index);
    rotations.erase(rotations.begin() + index);
}

void ModelManager::transformModel(const ModelTransformation &transformation, const int &index)
{
    if (std::holds_alternative<ModelMovement>(transformation))
    {
        ModelMovement movement = std::get<ModelMovement>(transformation);
        if (fabs(movement.angleX) > EPS)
        {
            rotateByX(movement.angleX, index);
        }
        if (fabs(movement.angleY) > EPS)
        {
            rotateByY(movement.angleY, index);
        }
        if (fabs(movement.angleZ) > EPS)
        {
            rotateByZ(movement.angleZ, index);
        }
        if (fabs(movement.dx) > EPS)
        {
            translateByX(movement.dx, index);
        }
        if (fabs(movement.dy) > EPS)
        {
            translateByY(movement.dy, index);
        }
        if (fabs(movement.dz) > EPS)
        {
            translateByZ(movement.dz, index);
        }
    }
    else
    {
        ModelAttributes attributes = std::get<ModelAttributes>(transformation);
        if (attributes.lengthBot >= 0)
        {
            models[index].changeBotLength(attributes.lengthBot);
        }
        if (attributes.lengthTop >= 0)
        {
            models[index].changeTopLength(attributes.lengthTop);
        }
        if (attributes.height >= 0)
        {
            models[index].changeHeight(attributes.height);
        }
        if (attributes.nVerts >= 0)
        {
            models[index].changeVerticesCount(attributes.nVerts);
        }
    }

}

void ModelManager::rotateByX(const double &angle, const int &index)
{
    double rad = angle * M_PI / 180;
    Matrix<double> rotateX(4, 4);
    rotateX.makeIdentity();
    rotateX[1][1] = cos(rad);
    rotateX[1][2] = sin(rad);
    rotateX[2][1] = -rotateX[1][2];
    rotateX[2][2] = rotateX[1][1];
    rotations[index] = rotations[index] * rotateX;
}

void ModelManager::rotateByY(const double &angle, const int &index)
{
    double rad = angle * M_PI / 180;
    Matrix<double> rotateY(4, 4);
    rotateY.makeIdentity();
    rotateY[0][0] = cos(rad);
    rotateY[0][2] = -sin(rad);
    rotateY[2][0] = - rotateY[0][2];
    rotateY[2][2] = rotateY[0][0];
    rotations[index] = rotations[index] * rotateY;
}

void ModelManager::rotateByZ(const double &angle, const int &index)
{
    double rad = angle * M_PI / 180;
    Matrix<double> rotateZ(4, 4);
    rotateZ.makeIdentity();
    rotateZ[0][0] = cos(rad);
    rotateZ[0][1] = sin(rad);
    rotateZ[1][0] = -rotateZ[0][1];
    rotateZ[1][1] = rotateZ[0][0];
    rotations[index] = rotations[index] * rotateZ;
}

Matrix<double> ModelManager::getModelView(const int &index) const
{
    Matrix<double> rotation = rotations[index];
    Point<3, double> translate = translations[index];
    Matrix<double> translation(4, 4);
    translation.makeIdentity();
    translation[3][0] = translate.x();
    translation[3][1] = translate.y();
    translation[3][2] = translate.z();
    return rotation * translation;
}
