#include "camera.h"

Camera::Camera()
    : direction(3),
      up(3),
      right(3)
{
}

Camera::Camera(const Point<3, double> &eye, const Point<3, double> &center, const MathVector<double> &top, const ViewFrustrum &frust)
    : Camera()
{
    position = eye;
    direction = center - eye;
    direction.normalise();
    right = (top ^ direction);
    right.normalise();
    up = direction ^ right;
    up.normalise();
    frustrum = frust;
}
