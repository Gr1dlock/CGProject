#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "scene/camera/cameramanager.h"
#include "scene/light/lightmanager.h"
#include "scene/model/modelmanager.h"
#include "scene/render/rendermanager.h"
#include "scene/scenecontainer.h"

enum class CameraParam{ YAW, PITCH, POS_X, POS_Y, POS_Z, NEAR_PLANE, FAR_PLANE, FOV, SENSITIVITY };

struct CameraChange
{
    CameraParam type;
    double value;
};

enum class ModelParam{ TOP, BOT, HEIGHT, VERTS };

struct ModelChange
{
    ModelParam type;
    double value;
};

using CameraTransformation = std::variant<CameraRotation, CameraMovement, CameraChange>;

using ModelTransformation = std::variant<ModelChange, ModelMovement>;

class Controller
{
public:
    Controller();
    Controller(QImage *frame, const int &screen_width, const int &screen_height, const CameraAttributes &cameraAttributes);
    void changeCamera(const CameraTransformation &transformation);
    inline int getObjectIndex(const int &x, const int &y) const { return renderManager.getIndexByPosition(x, y); }
    int addModel(const ModelAttributes &attributes);
    ModelAttributes getModelAttributes(const int &index);
    void deleteModel(const int &index);
    void changeModel(const ModelTransformation &transformation, const int &index);
    double getYaw();
    double getPitch();
    Point<3, double> getCameraPos();
    void deleteAllModels();
private:
    CameraManager cameraManager;
    LightManager lightManager;
    ModelManager modelManager;
    RenderManager renderManager;
    SceneContainer sceneContainer;
    void render();
};


#endif // CONTROLLER_H
