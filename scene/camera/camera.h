#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/geometry.hpp"

using namespace GeometrySpace;

struct ViewFrustrum
{
    double field_of_view;
    double near_plane;
    double far_plane;
    double aspect_ratio;
};

class Camera
{
public:
    Camera();
    Camera(const Point<3, double> &position, const MathVector<double> &direction, const MathVector<double> &up,
           const MathVector<double> &right, const ViewFrustrum &frustrum);
    inline void setPosition(const Point<3, double> &position) { position_ = position; }
    inline void setDirection(const MathVector<double> &direction) { direction_ = direction; }
    inline void setUp(const MathVector<double> &up) { up_ = up; }
    inline void setRight(const MathVector<double> &right) { right_ = right; }
    inline void setViewFrustrum(const ViewFrustrum &frustrum) { frustrum_ = frustrum; }
    inline Point<3, double> getPosition() const { return position_; }
    inline MathVector<double> getDirection() const { return direction_; }
    inline MathVector<double> getUp() const { return up_; }
    inline MathVector<double> getRight() const{ return right_; }
    inline ViewFrustrum getViewFrustrum() const{ return frustrum_; }
private:
    Point<3, double> position_;
    MathVector<double> direction_;
    MathVector<double> up_;
    MathVector<double> right_;
    ViewFrustrum frustrum_;
};


#endif // CAMERA_H
