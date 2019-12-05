#include "light.h"

Light::Light()
{

}

Light::Light(const LightAttributes &attributes)
    : position_(attributes.position),
      color_(attributes.color)
{
}
