#ifndef VIEW_H
#define VIEW_H

#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class ViewPort
{
public:
    ViewPort();
    ViewPort(const int &screen_width, const int &screen_height);
    void toScreen(Point<3, double> &point);
private:
    int width;
    int height;
};

#endif // VIEW_H
