#include "color.h"

Color::Color()
{
}

Color::Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue)
    : r(red),
      g(green),
      b(blue)
{
}

Color::Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue, const float &alpha)
    : r(red),
      g(green),
      b(blue),
      a(alpha)
{
}

Color Color::operator + (const Color &other) const
{
    Color result = *this;
    result.r += other.r;
    result.g += other.g;
    result.b += other.b;
    return result;
}

Color Color::operator - (const Color &other) const
{
    Color result = *this;
    result.r -= other.r;
    result.g -= other.g;
    result.b -= other.b;
    return result;
}

Color Color::operator * (float f) const
{
    Color result = *this;
    result.r = static_cast<unsigned char>(result.r * f);
    result.g = static_cast<unsigned char>(result.g * f);
    result.b = static_cast<unsigned char>(result.b * f);
    return result;
}
