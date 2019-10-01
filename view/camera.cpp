#include "camera.h"

Camera::Camera()
    : direction(3),
      up(3),
      right(3)
{
}

Camera::Camera(const Point<3, double> &eye, const Point<3, double> &center, const MathVector<double> &top)
    : Camera()
{
    position = eye;
    direction = center - eye;
    direction.normalise();
    right = (top ^ direction);
    right.normalise();
    up = direction ^ right;
    up.normalise();
}

Matrix<double> Camera::lookAt()
{
    Matrix<double> rotate(4,4);
    Matrix<double> translate(4,4);
    translate.makeIdentity();
    rotate[3][3] = 1;
    for (int i = 0; i < 3; i++)
    {
        rotate[i][0] = right[i];
        rotate[i][1] = up[i];
        rotate[i][2] = direction[i];
        translate[3][i] = -position[i];
    }
    return translate * rotate;
}
