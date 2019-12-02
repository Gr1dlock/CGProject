#include "color.h"

Color::Color()
{
}

Color::Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue)
    : r_(red),
      g_(green),
      b_(blue)
{
}

Color::Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue, const float &alpha)
    : r_(red),
      g_(green),
      b_(blue),
      a(alpha)
{
}

Color Color::operator + (const Color &other) const
{
    Color result;
    result.r_ = std::min(r_ + other.r_, 255);
    result.g_ = std::min(g_ + other.g_, 255);
    result.b_ = std::min(b_ + other.b_, 255);
    return result;
}

Color Color::operator - (const Color &other) const
{
    Color result;
    result.r_ = std::max(r_ - other.r_, 0);
    result.g_ = std::max(g_ - other.g_, 0);
    result.b_ = std::max(b_ - other.b_, 0);
    return result;
}

Color Color::operator *(const Color &other) const
{
    Color result;
    result.r_ = std::min(r_ * other.r_, 255);
    result.g_ = std::min(g_ * other.g_, 255);
    result.b_ = std::min(b_ * other.b_, 255);
    return result;
}

Color Color::operator * (const double &f) const
{
    Color result;
    result.r_ = std::min(static_cast<int>(r_ * f), 255);
    result.g_ = std::min(static_cast<int>(g_ * f), 255);
    result.b_ = std::min(static_cast<int>(b_ * f), 255);
    return result;
}
