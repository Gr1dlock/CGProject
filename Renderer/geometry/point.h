#ifndef POINT_H
#define POINT_H

#include "geometry.h"
#include <iostream>

namespace GeometrySpace
{
    template <int size, typename T>
    class Point
    {
    private:
        T *data;
    public:
        inline T x() const { return data[0]; }
        inline T y() const { return data[1]; }
        inline T z() const { return data[2]; }
        inline T w() const { return data[3]; }
        inline void setX(T x) { data[0] = x; }
        inline void setY(T y) { data[1] = y; }
        inline void setZ(T z) { data[2] = z; }
        inline void setW(T w) { data[3] = w; }
        Point();
        Point(const T &x, const T &y);
        Point(const T &x, const T &y, const T &z);
        Point(const T &x, const T &y, const T &z, const T &w);
        Point(const Point<size, T> &other);
        Point(const Point<size - 1, T> &other);
        Point(const Point<size + 1, T> &other);
        Point<size, T> operator + (const Point<size, T> &other) const;
        Point<size, T> operator - (const Point<size, T> &other) const;
        Point<size, T> operator * (double f) const;
        Point<size, T> operator * (const Matrix<T> &other) const;
        Point<size, T> &operator = (const Point<size, T> &other) const;
        Point<size, T> &operator = (const Point<size, T> &other);
        Point<size, T> &operator = (const Point<size - 1, T> &other) const;
        Point<size, T> &operator = (const Point<size - 1, T> &other);
        Point<size, T> &operator = (const Point<size + 1, T> &other) const;
        Point<size, T> &operator = (const Point<size + 1, T> &other);
        T &operator [] (int index);
        const T &operator [] (const int &index) const;
        ~Point();
    };
}
#endif // POINT_H
