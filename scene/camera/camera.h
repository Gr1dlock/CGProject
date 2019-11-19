#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/geometry.hpp"

using namespace GeometrySpace;

inline double radians(const double &angle) { return angle * M_PI / 180; }
inline double degrees(const double &angle) { return angle * 180 / M_PI; }

struct ViewFrustrum
{
    double field_of_view;
    double near_plane;
    double far_plane;
    double aspect_ratio;
};

struct CameraAttributes
{
    Point<3, double> position;
    double yaw;
    double pitch;
    MathVector<double> top;
    ViewFrustrum frustrum;
};

class Camera
{
public:
    Camera();
    Camera(const CameraAttributes &attributes);
    inline void setPosition(const Point<3, double> &position) { position_ = position; }
    inline void setDirection(const MathVector<double> &direction) { direction_ = direction; }
    inline void setUp(const MathVector<double> &up) { up_ = up; }
    inline void setRight(const MathVector<double> &right) { right_ = right; }
    inline void setTop(const MathVector<double> &top) { top_ = top; }
    inline void setYaw(const double &yaw) { yaw_ = yaw; }
    inline void setPitch(const double &pitch) { pitch_ = pitch; }
    inline void setViewFrustrum(const ViewFrustrum &frustrum) { frustrum_ = frustrum; }
    inline Point<3, double> getPosition() const { return position_; }
    inline MathVector<double> getDirection() const { return direction_; }
    inline MathVector<double> getUp() const { return up_; }
    inline MathVector<double> getRight() const { return right_; }
    inline ViewFrustrum getViewFrustrum() const { return frustrum_; }
    inline MathVector<double> getTop() const { return top_; }
    inline double getYaw() const { return yaw_; }
    inline double getPitch() const { return pitch_; }
    void updateCoords();
private:
    Point<3, double> position_;
    MathVector<double> direction_;
    MathVector<double> up_;
    MathVector<double> right_;
    MathVector<double> top_;
    double yaw_;
    double pitch_;
    ViewFrustrum frustrum_;
};


#endif // CAMERA_H
