#include "cameramanager.h"

CameraManager::CameraManager()
{
}

Matrix<double> CameraManager::getLookAt()
{
    Matrix<double> rotate(4,4);
    Matrix<double> translate(4,4);
    MathVector<double> direction = camera.getDirection();
    MathVector<double> up = camera.getUp();
    MathVector<double> right = camera.getRight();
    Point<3, double> position = camera.getPosition();
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

Matrix<double> CameraManager::getProjection()
{
    ViewFrustrum frustrum = camera.getViewFrustrum();
    Matrix<double> projection(4,4);
    projection[1][1] = 1 / tan(frustrum.field_of_view / 2 * M_PI / 180);
    projection[0][0] = projection[1][1] /frustrum. aspect_ratio;
    projection[2][2] = (frustrum.far_plane + frustrum.near_plane) / (frustrum.far_plane - frustrum.near_plane);
    projection[3][2] = -2 * frustrum.near_plane * frustrum.far_plane / (frustrum.far_plane - frustrum.near_plane);
    projection[2][3] = 1;
    return projection;
}
