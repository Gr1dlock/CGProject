#ifndef LIGHT_H
#define LIGHT_H

#include "color/color.h"
#include "geometry/geometry.hpp"

using namespace GeometrySpace;

struct LightAttributes
{
    Vector3D<double> position;
    Color color;
};

class Light
{
public:
    Light();
    Light(const LightAttributes &attributes);
    inline void setPosition(const Vector3D<double> &position) { position_ = position; }
    inline void setColor(const Color &color) { color_ = color; }
    inline Color getColor() const { return color_; }
    inline Vector3D<double> getPosition() const { return position_; }
private:
    Vector3D<double> position_;
    Color color_;
};

#endif // LIGHT_H
