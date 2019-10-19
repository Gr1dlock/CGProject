#include "viewport.h"

ViewPort::ViewPort()
{
}

ViewPort::ViewPort(const int &screen_width, const int &screen_height)
    : width(screen_width), height(screen_height)
{
}

void ViewPort::toScreen(Point<3, double> &point)
{
    point.setX(round((point.x() + 1) * 0.5 * width));
    point.setY(round(height - (point.y() + 1) * 0.5 * height));
}
