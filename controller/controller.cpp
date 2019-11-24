#include "controller.h"

#include <QtDebug>

Controller::Controller()
{

}

Controller::Controller(QImage *frame, const int &screen_width, const int &screen_height, const CameraAttributes &cameraAttributes)
{
    renderManager = RenderManager(frame, screen_width, screen_height);
    cameraManager = CameraManager(2, 0.25);
    Camera camera(cameraAttributes);
    sceneContainer.setCamera(camera);
    render();
}

int Controller::addModel(const ModelAttributes &attributes)
{
    Cube model(attributes);
    sceneContainer.addModel(model);
    render();
    return sceneContainer.countModels();
}

ModelAttributes Controller::getModelAttributes(const int &index)
{
    const Cube &model = sceneContainer.getModel(index);
    return model.getAttributes();
}

void Controller::deleteModel(const int &index)
{
    sceneContainer.deleteModel(index);
    render();
}

void Controller::changeModel(const ModelTransformation &transformation, const int &index)
{
    Cube &model = sceneContainer.getModel(index);
    if (std::holds_alternative<ModelMovement>(transformation))
    {
        ModelMovement movement = std::get<ModelMovement>(transformation);
        if (fabs(movement.angleX) > EPS)
        {
            modelManager.rotateByX(model, movement.angleX);
        }
        if (fabs(movement.angleY) > EPS)
        {
            modelManager.rotateByY(model, movement.angleY);
        }
        if (fabs(movement.angleZ) > EPS)
        {
            modelManager.rotateByZ(model, movement.angleZ);
        }
        if (fabs(movement.dx) > EPS)
        {
            modelManager.translateByX(model, movement.dx);
        }
        if (fabs(movement.dy) > EPS)
        {
            modelManager.translateByY(model, movement.dy);
        }
        if (fabs(movement.dz) > EPS)
        {
            modelManager.translateByZ(model, movement.dz);
        }
    }
    else
    {
        ModelChange change = std::get<ModelChange>(transformation);
        switch (change.type)
        {
        case ModelParam::TOP:
            model.changeTopLength(change.value);
            break;
        case ModelParam::BOT:
            model.changeBotLength(change.value);
            break;
        case ModelParam::HEIGHT:
            model.changeHeight(change.value);
            break;
        case ModelParam::VERTS:
            model.changeVerticesCount(change.value);
            break;
        default:
            break;
        }
    }
    render();
}

double Controller::getYaw()
{
    Camera &camera = sceneContainer.getCamera();
    return camera.getYaw();
}

double Controller::getPitch()
{
    Camera &camera = sceneContainer.getCamera();
    return camera.getPitch();
}

Point<3, double> Controller::getCameraPos()
{
    Camera &camera = sceneContainer.getCamera();
    return camera.getPosition();
}

void Controller::deleteAllModels()
{
    sceneContainer.deleteAllModels();
    render();
}

void Controller::changeCamera(const CameraTransformation &transformation)
{
    Camera &camera = sceneContainer.getCamera();
    if (std::holds_alternative<CameraMovement>(transformation))
    {
        CameraMovement movement = std::get<CameraMovement>(transformation);
        cameraManager.move(camera, movement);
    }
    else if (std::holds_alternative<CameraRotation>(transformation))
    {
        CameraRotation rotation = std::get<CameraRotation>(transformation);
        cameraManager.rotate(camera, rotation);
    }
    else
    {
        CameraChange change = std::get<CameraChange>(transformation);
        switch (change.type)
        {
        case CameraParam::YAW:
            camera.setYaw(change.value);
            camera.updateCoords();
            break;
        case CameraParam::PITCH:
            camera.setPitch(change.value);
            camera.updateCoords();
            break;
        case CameraParam::FOV:
        {
            ViewFrustrum frustrum = camera.getViewFrustrum();
            frustrum.field_of_view = change.value;
            camera.setViewFrustrum(frustrum);
            break;
        }
        case CameraParam::NEAR_PLANE:
        {
            ViewFrustrum frustrum = camera.getViewFrustrum();
            frustrum.near_plane = change.value;
            camera.setViewFrustrum(frustrum);
            break;
        }
        case CameraParam::FAR_PLANE:
        {
            ViewFrustrum frustrum = camera.getViewFrustrum();
            frustrum.far_plane = change.value;
            camera.setViewFrustrum(frustrum);
            break;
        }
        case CameraParam::POS_X:
        {
            Point<3, double> position = camera.getPosition();
            position.setX(change.value);
            camera.setPosition(position);
            break;
        }
        case CameraParam::POS_Y:
        {
            Point<3, double> position = camera.getPosition();
            position.setY(change.value);
            camera.setPosition(position);
            break;
        }
        case CameraParam::POS_Z:
        {
            Point<3, double> position = camera.getPosition();
            position.setZ(change.value);
            camera.setPosition(position);
            break;
        }
        case CameraParam::SENSITIVITY:
            cameraManager.setSensitivity(change.value);
            break;
        default:
            break;
        }
    }
    render();
}

void Controller::render()
{
    Camera camera = sceneContainer.getCamera();
    renderManager.clearFrame();
    Matrix<double> vpMatrix = cameraManager.getLookAt(camera) * cameraManager.getProjection(camera);
    Matrix<double> modelMatrix(4, 4);
    Shader shader;
    shader.setCameraPosition(camera.getPosition());
    shader.setLightPosition(Point<3, double>(0, 150, 0));
    for (int i = 0; i < sceneContainer.countModels(); i++)
    {
        Cube model = sceneContainer.getModel(i);
        modelMatrix = modelManager.getModelView(model);
        shader.setModelMatrix(modelMatrix);
        shader.setVpMatrix(vpMatrix);
        Material material{ Color(255, 0, 0), Color(255, 255, 255), 128};
        shader.setMaterial(material);
        shader.setLightColor(Color(100, 100, 100));
        renderManager.renderModel(model, shader, i);
    }
}
