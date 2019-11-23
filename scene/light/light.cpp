#include "light.h"

Light::Light()
{

}

Light::Light(const Point<3, double> &position, const Color &color)
    : position_(position),
      color_(color)
{
}
