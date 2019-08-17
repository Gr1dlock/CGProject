#ifndef POINT_H
#define POINT_H

#include "geometry.h"

namespace GeometrySpace
{
    template <typename T>
    class Point2D
    {
    private:
        T _x, _y;
    public:
        Point2D() {}
        Point2D(T x, T y);
        template <typename U>
        Point2D(const Point2D<U> &other);
        T x() const { return _x; }
        T y() const { return _y; }
        void setX(T x) { _x = x; }
        void setY(T y) { _y = y; }
        Point2D<T> operator + (const Point2D<T> &other) const;
        Point2D<T> operator - (const Point2D<T> &other) const;
        Point2D<T> operator * (double f) const;
        T &operator [] (int index);
        const T &operator [] (const int &index) const;
    };

    template <typename T>
    class Point3D
    {
    private:
        T _x, _y, _z;
    public:
        T x() const { return _x; }
        T y() const { return _y; }
        T z() const { return _z; }
        void setX(T x) { _x = x; }
        void setY(T y) { _y = y; }
        void setZ(T z) { _z = z; }
        Point3D() {}
        Point3D(T x, T y, T z);
        template<typename U>
        Point3D(const Point3D<U> &other);
        Point3D<T> operator + (const Point3D<T> &other) const;
        Point3D<T> operator - (const Point3D<T> &other) const;
        Point3D<T> operator * (double f) const;
        T &operator [] (int index);
        const T &operator [] (const int &index) const;
    };
}
#endif // POINT_H
