#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "scene/camera/camera.h"

class CameraManager
{
public:
    CameraManager();
    inline void setCamera(const Camera &cam) { camera = cam; }
//    void yaw();
//    void pitch();
//    void move();
    Matrix<double> getLookAt();
    Matrix<double> getProjection();
private:
    Camera camera;
};

#endif // CAMERAMANAGER_H
