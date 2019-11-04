#include "cameramanager.h"

#include <QtDebug>

CameraManager::CameraManager()
{
}

CameraManager::CameraManager(const CameraAttributes &attributes, const double &speed, const double &sensitivity)
    : speed_(speed),
      sensitivity_(sensitivity)
{
    setCamera(attributes);
}

void CameraManager::setCamera(const CameraAttributes &attributes)
{
    camera_ = Camera();
    yaw_ = radians(attributes.yaw);
    pitch_ = radians(attributes.pitch);
    top_ = attributes.top;
    camera_.setPosition(attributes.position);
    camera_.setViewFrustrum(attributes.frustrum);
    updateCoords();
}

void CameraManager::setYaw(const double &yaw)
{
    yaw_ = radians(yaw);
    updateCoords();
}

void CameraManager::setPitch(const double &pitch)
{
    pitch_ = radians(pitch);
    updateCoords();
}

void CameraManager::transformCamera(const CameraTransformation &transformation)
{
    if (std::holds_alternative<CameraMovement>(transformation))
    {
        CameraMovement movement = std::get<CameraMovement>(transformation);
        move(movement);
    }
    else if (std::holds_alternative<CameraRotation>(transformation))
    {
        CameraRotation rotation = std::get<CameraRotation>(transformation);
        rotate(rotation);
    }
    else
    {
        CameraAttributes attributes = std::get<CameraAttributes>(transformation);
        setCamera(attributes);
    }
}

void CameraManager::rotate(const CameraRotation &rotation)
{
    yaw_ += radians(rotation.dYaw * sensitivity_);
    pitch_ += radians(rotation.dPitch * sensitivity_);
    if (pitch_ > M_PI / 2)
    {
        pitch_ = M_PI / 2;
    }
    else if (pitch_< -M_PI / 2)
    {
        pitch_ = -M_PI / 2;
    }
    updateCoords();
}

void CameraManager::move(const CameraMovement &movement)
{
    Point<3, double> position = camera_.getPosition();
    MathVector<double> direction = camera_.getDirection();
    MathVector<double> right = camera_.getRight();
    if (movement.forward)
        position += direction * speed_;
    if (movement.backward)
        position -= direction * speed_;
    if (movement.left)
        position -= right * speed_;
    if (movement.right)
        position += right * speed_;
    camera_.setPosition(position);
}

Matrix<double> CameraManager::getLookAt() const
{
    Matrix<double> rotate(4,4);
    Matrix<double> translate(4,4);
    MathVector<double> direction = camera_.getDirection();
    MathVector<double> up = camera_.getUp();
    MathVector<double> right = camera_.getRight();
    Point<3, double> position = camera_.getPosition();
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

Matrix<double> CameraManager::getProjection() const
{
    ViewFrustrum frustrum = camera_.getViewFrustrum();
    Matrix<double> projection(4,4);
    projection[1][1] = 1 / tan(radians(frustrum.field_of_view / 2));
    projection[0][0] = projection[1][1] /frustrum. aspect_ratio;
    projection[2][2] = (frustrum.far_plane + frustrum.near_plane) / (frustrum.far_plane - frustrum.near_plane);
    projection[3][2] = -2 * frustrum.near_plane * frustrum.far_plane / (frustrum.far_plane - frustrum.near_plane);
    projection[2][3] = 1;
    return projection;
}

void CameraManager::updateCoords()
{
    MathVector<double> direction(3);
    direction[0] = cos(yaw_) * cos(pitch_);
    direction[1] = sin(pitch_);
    direction[2] = sin(yaw_) * cos(pitch_);
    direction.normalize();
    camera_.setDirection(direction);
    MathVector<double> right = top_ ^ direction;
    right.normalize();
    camera_.setRight(right);
    MathVector<double> up = direction ^ right;
    up.normalize();
    camera_.setUp(up);
}
