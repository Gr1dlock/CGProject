#ifndef POINT_HPP
#define POINT_HPP

#include "mathpoint.h"

namespace GeometrySpace
{
template<typename T>
T &Point2D<T>::operator [](int index)
{
    if (index == 0)
        return _x;
    else if (index == 1)
        return _y;
    else
        throw std::out_of_range("Index out of range");
}

template<typename T>
const T &Point2D<T>::operator [](const int &index) const
{
    if (index == 0)
        return _x;
    else if (index == 1)
        return _y;
    else
        throw std::out_of_range("Index out of range");
}

template <typename T>
template <typename U>
Point2D<T>::Point2D(const Point2D<U> &other)
{
    if (std::is_same<T, int>::value && std::is_same<U, double>::value)
    {
        for (int i = 0; i < 2; i++)
            (*this)[i] = static_cast<int>(round(other[i]));
    }
    else
    {
        for (int i = 0; i < 2; i++)
            (*this)[i] = other[i];
    }
}


template<typename T>
Point2D<T>::Point2D(T x, T y)
    :_x(x), _y(y)
{
}

template<typename T>
Point2D<T> Point2D<T>::operator + (const Point2D<T> &v) const
{
    Point2D result(*this);
    for (int i = 0; i < 2; i++)
        result[i] += v[i];
    return result;
}

template<typename T>
Point2D<T> Point2D<T>::operator - (const Point2D<T> &v) const
{
    Point2D result(*this);
    for (int i = 0; i < 2; i++)
        result[i] -= v[i];
    return result;
}

template<typename T>
Point2D<T> Point2D<T>::operator *(double f) const
{
    Point2D result(*this);
    for (int i = 0; i < 3; i++)
        result[i] *= f;
    return result;
}

template <typename T>
template <typename U>
Point3D<T>::Point3D(const Point3D<U> &other)
{
    if (std::is_same<T, int>::value && std::is_same<U, double>::value)
    {
        for (int i = 0; i < 3; i++)
            (*this)[i] = static_cast<int>(round(other[i]));
    }
    else
    {
        for (int i = 0; i < 3; i++)
            (*this)[i] = other[i];
    }
}

template<typename T>
Point3D<T>::Point3D(T x, T y, T z)
    :_x(x), _y(y), _z(z)
{
}

template<typename T>
Point3D<T> Point3D<T>::operator + (const Point3D<T> &v) const
{
    Point3D result(*this);
    for (int i = 0; i < 3; i++)
        result[i] += v[i];
    return result;
}

template<typename T>
Point3D<T> Point3D<T>::operator - (const Point3D<T> &v) const
{
    Point3D result(*this);
    for (int i = 0; i < 3; i++)
        result[i] -= v[i];
    return result;
}

template<typename T>
Point3D<T> Point3D<T>::operator *(double f) const
{
    Point3D result(*this);
    for (int i = 0; i < 3; i++)
        result[i] *= f;
    return result;
}

template<typename T>
T &Point3D<T>::operator [](int index)
{
    if (index == 0)
        return _x;
    else if (index == 1)
        return _y;
    else if (index == 2)
        return _z;
    else
        throw std::out_of_range("Index out of range");
}

template<typename T>
const T &Point3D<T>::operator [](const int &index) const
{
    if (index == 0)
        return _x;
    else if (index == 1)
        return _y;
    else if (index == 2)
        return _z;
    else
        throw std::out_of_range("Index out of range");
}
}
#endif // POINT_HPP
