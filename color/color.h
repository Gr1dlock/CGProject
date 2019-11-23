#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color
{
public:
    Color();
    Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue);
    Color(const unsigned char &red, const unsigned char &green, const unsigned char &blue, const float &alpha);
    inline void setRed(const unsigned char &red) { r = red; }
    inline void setGreen(const unsigned char &green) { g = green; }
    inline void setBlue(const unsigned char &blue) { b = blue; }
    inline void setAlpha(const float &alpha) { a = alpha; }
    inline unsigned char gerRed() const { return r; }
    inline unsigned char getGreen() const  { return g; }
    inline unsigned char getBlue() const { return b; }
    inline float getAlpha() const { return a; }
    Color operator + (const Color &other) const;
    Color operator - (const Color &other) const;
    Color operator * (const Color &other) const;
    Color operator * (float f) const;
private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    float a;
};

#endif // COLOR_H
