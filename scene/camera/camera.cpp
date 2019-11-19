#include "camera.h"

Camera::Camera()
    : direction_(3),
      up_(3),
      right_(3),
      top_(3)
{
}

Camera::Camera(const CameraAttributes &attributes)
    : Camera()
{
    position_ = attributes.position;
    top_ = attributes.top;
    yaw_ = attributes.yaw;
    pitch_ = attributes.pitch;
    frustrum_ = attributes.frustrum;
    updateCoords();
}

void Camera::updateCoords()
{
    double yaw = radians(yaw_);
    double pitch = radians(pitch_);
    direction_[0] = cos(yaw) * cos(pitch);
    direction_[1] = sin(pitch);
    direction_[2] = sin(yaw) * cos(pitch);
    direction_.normalize();
    right_ = top_ ^ direction_;
    right_.normalize();
    up_ = direction_ ^ right_;
    up_.normalize();
}
