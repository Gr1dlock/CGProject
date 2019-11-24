#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <QColor>

class Color
{
public:
    Color();
    Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue);
    Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue, const float &alpha);
    inline void setRed(const unsigned char &red) { r_ = red; }
    inline void setGreen(const unsigned char &green) { g_ = green; }
    inline void setBlue(const unsigned char &blue) { b_ = blue; }
    inline void setAlpha(const float &alpha) { a = alpha; }
    inline unsigned char r() const { return r_; }
    inline unsigned char g() const  { return g_; }
    inline unsigned char b() const { return b_; }
    inline QRgb rgb() { return qRgb(r_, g_, b_); }
    inline float getAlpha() const { return a; }
    Color operator + (const Color &other) const;
    Color operator - (const Color &other) const;
    Color operator * (const Color &other) const;
    Color operator * (const double &f) const;
private:
    unsigned char r_;
    unsigned char g_;
    unsigned char b_;
    float a;
};

#endif // COLOR_H
