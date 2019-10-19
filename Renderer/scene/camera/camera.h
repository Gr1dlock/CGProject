#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/geometry.hpp"

struct ViewFrustrum
{
    double field_of_view;
    double near_plane;
    double far_plane;
    double aspect_ratio;
};

using namespace GeometrySpace;

class Camera
{
public:
    Camera();
    Camera(const Point<3, double> &eye, const Point<3, double> &center, const MathVector<double> &top, const ViewFrustrum &frust);
    inline void setPosition(const Point<3, double> &point) { position = point; }
    inline void setDirection(const MathVector<double> &vect) { direction = vect; }
    inline void setUp(const MathVector<double> &vect) { up = vect; }
    inline void setRight(const MathVector<double> &vect) { right = vect; }
    inline void setViewFrustrum(const ViewFrustrum &frust) { frustrum = frust; }
    inline Point<3, double> getPosition() const { return position; }
    inline MathVector<double> getDirection() const { return direction; }
    inline MathVector<double> getUp() const { return up; }
    inline MathVector<double> getRight() const{ return right; }
    inline ViewFrustrum getViewFrustrum() const{ return frustrum; }
private:
    Point<3, double> position;
    MathVector<double> direction;
    MathVector<double> up;
    MathVector<double> right;
    ViewFrustrum frustrum;
};


#endif // CAMERA_H
