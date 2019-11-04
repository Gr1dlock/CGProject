#include "camera.h"

Camera::Camera()
    : direction_(3),
      up_(3),
      right_(3)
{
}

Camera::Camera(const Point<3, double> &position, const MathVector<double> &direction, const MathVector<double> &up,
       const MathVector<double> &right, const ViewFrustrum &frustrum)
    : Camera()
{
    position_ = position;
    direction_ = direction;
    up_ = up;
    right_ = right;
    frustrum_ = frustrum;
}
