#include "modelmanager.h"

ModelManager::ModelManager()
{

}

void ModelManager::addModel(const Cube &model)
{
    models.push_back(model);
    translations.push_back(Point<3, double>(0, 0, 0));
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

void ModelManager::translateByX(const double &translation, const int &index)
{
    translations[index] = translations[index] + Point<3, double>(translation, 0, 0);
}

void ModelManager::translateByY(const double &translation, const int &index)
{
    translations[index] = translations[index] + Point<3, double>(0, translation, 0);
}

void ModelManager::translateByZ(const double &translation, const int &index)
{
    translations[index] = translations[index] + Point<3, double>(0, 0, translation);
}

Matrix<double> ModelManager::getModelView(const int &index)
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
