#include "scenemanager.h"

#include <QtDebug>

SceneManager::SceneManager()
{
}

SceneManager::SceneManager(QImage *frame, const int &screen_width, const int &screen_height, const CameraAttributes &attributes)
{
    renderManager = RenderManager(frame, screen_width, screen_height);
    cameraManager = CameraManager(attributes, 3, 0.25);
    render();
}

void SceneManager::addModel(const ModelAttributes &attributes)
{
    Cube model(attributes);
    modelManager.addModel(model);
    render();
}

void SceneManager::removeModel(const int &index)
{
    modelManager.deleteModel(index);
    render();
}

void SceneManager::changeModel(const ModelTransformation &transformation, const int &index)
{
    modelManager.transformModel(transformation, index);
    render();
}

void SceneManager::setCamera(const CameraAttributes &attributes)
{
    cameraManager.setCamera(attributes);
    render();
}

void SceneManager::changeCamera(const CameraTransformation &transformation)
{
    cameraManager.transformCamera(transformation);
    render();
}

void SceneManager::render()
{
    renderManager.clearFrame();
    Point<3, double> cameraPos = cameraManager.getCameraPosition();
    Matrix<double> perspectiveMatrix = cameraManager.getLookAt() * cameraManager.getProjection();
    for (int i = 0; i < modelManager.countModels(); i++)
    {
        Cube model = modelManager.getModel(i);
//        for (int i = 0; i < 4; i ++)
//            qDebug() << perspectiveMatrix[i][0] << perspectiveMatrix[i][1] << perspectiveMatrix[i][2] <<perspectiveMatrix[i][3];
        Matrix<double> viewMatrix = modelManager.getModelView(i) * perspectiveMatrix;

        renderManager.renderModel(model, viewMatrix, i, cameraPos);
    }
}

