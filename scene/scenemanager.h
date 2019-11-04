#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <scene/camera/cameramanager.h>
#include <scene/light/lightmanager.h>
#include <scene/model/modelmanager.h>
#include <scene/render/rendermanager.h>

class SceneManager
{
public:
    SceneManager();
    SceneManager(QImage *frame, const int &screen_width, const int &screen_height, const CameraAttributes &attributes);

    void addModel(const ModelAttributes &attributes);
    void removeModel(const int &index);
    void changeModel(const ModelTransformation &transformation, const int &index);

    void setCamera(const CameraAttributes &attributes);
    void changeCamera(const CameraTransformation &transformation);

    void setLight();
    void changeLight();

    inline int getObjectIndex(const int &x, const int &y) const { return renderManager.getIndexByPosition(x, y); }

private:
    CameraManager cameraManager;
    LightManager lightManager;
    ModelManager modelManager;
    RenderManager renderManager;
    void render();
};

#endif // SCENEMANAGER_H
