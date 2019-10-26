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
    SceneManager(QImage *frame, const int &screen_width, const int &screen_height);

    void addModel();
    void removeModel();
    void changeModel();

    void setCamera();
    void changeCamera();

    void setLight();
    void changeLight();
private:
    CameraManager camera_manager;
    LightManager light_manager;
    ModelManager model_manager;
    RenderManager render_manager;
    void render();
};

#endif // SCENEMANAGER_H
