#include "light.h"

Light::Light()
{

}

Light::Light(const Vector3D<double> &position, const Color &color)
    : position_(position),
      color_(color)
{
}
