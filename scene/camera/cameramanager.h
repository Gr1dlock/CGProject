#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <variant>

#include "scene/camera/camera.h"

inline double radians(const double &angle) { return angle * M_PI / 180; }

struct CameraRotation
{
    double dYaw;
    double dPitch;
};

struct CameraMovement
{
    bool forward;
    bool backward;
    bool left;
    bool right;
};

struct CameraAttributes
{
    Point<3, double> position;
    double yaw;
    double pitch;
    MathVector<double> top;
    ViewFrustrum frustrum;
};

using CameraTransformation = std::variant<CameraRotation, CameraMovement, CameraAttributes>;

class CameraManager
{
public:
    CameraManager();
    CameraManager(const CameraAttributes &attributes, const double &speed, const double &sensitivity);
    void setCamera(const CameraAttributes &attributes);
    void setYaw(const double &yaw);
    void setPitch(const double &pitch);
    void transformCamera(const CameraTransformation &transformation);
    inline void setSpeed(const double &speed) { speed_ = speed; }
    inline void setSensitivity(const double &sensitivity) { sensitivity_ = sensitivity; }
    inline double getYaw() const { return yaw_; }
    inline double getPitch() const { return pitch_; }
    inline double getSpeed() const { return speed_; }
    inline double getSensitivity() const{ return sensitivity_; }
    inline Point<3, double> getCameraPosition() const { return camera_.getPosition(); }
    void rotate(const CameraRotation &rotation);
    void move(const CameraMovement &movement);
    Matrix<double> getLookAt() const;
    Matrix<double> getProjection() const;
private:
    void updateCoords();
    Camera camera_;
    double yaw_;
    double pitch_;
    MathVector<double> top_;
    double speed_;
    double sensitivity_;
};

#endif // CAMERAMANAGER_H
