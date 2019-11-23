#ifndef LIGHT_H
#define LIGHT_H

#include "color/color.h"
#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class Light
{
public:
    Light();
    Light(const Point<3, double> &position, const Color &color);
    inline void setPosition(const Point<3, double> &position) { position_ = position; }
    inline void setColor(const Color &color) { color_ = color; }
    inline Color getColor() const { return color_; }
    inline Point<3, double> getPosition() const { return position_; }
private:
    Point<3, double> position_;
    Color color_;
};

#endif // LIGHT_H
