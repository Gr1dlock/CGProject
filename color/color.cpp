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
    Color result;
    result.r = std::min(r + other.r, 255);
    result.g = std::min(g + other.g, 255);
    result.b = std::min(b + other.b, 255);
    return result;
}

Color Color::operator - (const Color &other) const
{
    Color result;
    result.r = std::max(r - other.r, 0);
    result.g = std::max(g - other.g, 0);
    result.b = std::max(b - other.b, 0);
    return result;
}

Color Color::operator *(const Color &other) const
{
    Color result;
    result.r = std::min(r * other.r, 255);
    result.g = std::min(g * other.g, 255);
    result.b = std::min(b * other.b, 255);
    return result;
}

Color Color::operator * (float f) const
{
    Color result;
    result.r = std::min(static_cast<int>(r * f), 255);
    result.g = std::min(static_cast<int>(g * f), 255);
    result.b = std::min(static_cast<int>(b * f), 255);
    return result;
}
