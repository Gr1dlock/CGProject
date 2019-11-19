#ifndef POINT_HPP
#define POINT_HPP

#include "point.h"

namespace GeometrySpace
{

    template<int size, typename T>
    Point<size, T>::Point()
    {
        try
        {
            data = new T[size];
        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template<int size, typename T>
    Point<size, T>::Point(const T &x, const T &y)
        : Point()
    {
        data[0] = x;
        data[1] = y;
    }

    template<int size, typename T>
    Point<size, T>::Point(const T &x, const T &y, const T &z)
        : Point()
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    template<int size, typename T>
    Point<size, T>::Point(const T &x, const T &y, const T &z, const T &w)
        : Point()
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }

    template<int size, typename T>
    Point<size, T>::Point(const Point<size, T> &other)
        :Point()
    {
        for (int i = 0; i < size; i++)
            data[i] = other[i];
    }

    template<int size, typename T>
    Point<size, T>::Point(const Point<size - 1, T> &other)
        :Point()
    {
        for (int i = 0; i < size - 1; i++)
            data[i] = other[i];
        data[size - 1] = 1;
    }

    template<int size, typename T>
    Point<size, T>::Point(const Point<size + 1, T> &other)
        :Point()
    {
        for (int i = 0; i < size; i++)
            data[i] = other[i] / other[size];
    }

    template<int size, typename T>
    Point<size, T> Point<size, T>::operator + (const Point<size, T> &other) const
    {
        Point result(*this);
        for (int i = 0; i < size; i++)
            result[i] += other[i];
        return result;
    }

    template<int size, typename T>
    Point<size, T> Point<size, T>::operator - (const Point<size, T> &other) const
    {
        Point result(*this);
        for (int i = 0; i < size; i++)
            result[i] -= other[i];
        return result;
    }

    template<int size, typename T>
    Point<size, T> Point<size, T>::operator + (const MathVector<T> &other) const
    {
        Point result(*this);
        for (int i = 0; i < size; i++)
            result[i] += other[i];
        return result;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator += (const Point<size, T> &other)
    {
        for (int i = 0; i < size; i++)
            data[i] += other[i];
        return *this;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator -= (const Point<size, T> &other)
    {
        for (int i = 0; i < size; i++)
            data[i] -= other[i];
        return *this;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator += (const MathVector<T> &other)
    {
        for (int i = 0; i < size; i++)
            data[i] += other[i];
        return *this;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator -= (const MathVector<T> &other)
    {
        for (int i = 0; i < size; i++)
            data[i] -= other[i];
        return *this;
    }

    template<int size, typename T>
    Point<size, T> Point<size, T>::operator - (const MathVector<T> &other) const
    {
        Point result(*this);
        for (int i = 0; i < size; i++)
            result[i] -= other[i];
        return result;
    }

    template<int size, typename T>
    Point<size, T> Point<size, T>::operator *(double f) const
    {
        Point result(*this);
        for (int i = 0; i < size; i++)
            result[i] *= f;
        return result;
    }

    template<int size, typename T>
    T &Point<size, T>::operator [](int index)
    {
        if (index < size)
            return data[index];
        throw std::out_of_range("Index out of range");
    }

    template<int size, typename T>
    const T &Point<size, T>::operator [](const int &index) const
    {
        if (index < size)
            return data[index];
        throw std::out_of_range("Index out of range");
    }

    template<int size, typename T>
    Point<size, T>::~Point()
    {
        delete [] data;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator = (const Point<size, T> &other)
    {
        for (int i = 0; i < size; i++)
            data[i] = other[i];
        return *this;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator = (const Point<size - 1, T> &other)
    {
        for (int i = 0; i < size - 1; i++)
            data[i] = other[i];
        data[size - 1] = 1;
        return *this;
    }

    template<int size, typename T>
    Point<size, T> &Point<size, T>::operator = (const Point<size + 1, T> &other)
    {
        for (int i = 0; i < size; i++)
            data[i] = other[i] / other[size];
        return *this;
    }

    template<int size, typename T>
    Point<size, T> Point<size, T>::operator * (const Matrix<T> &other) const
    {
        if (size == other.countRows() && size == other.countCols())
        {
            Point<size, T> result;
            for (int i = 0; i < size; i++)
            {
                result[i] = 0;
                for (int j = 0; j < size; j++)
                {
                    result[i] += (*this)[j] * other[j][i];
                }
            }
            return result;
        }
        if (size == other.countRows() - 1 && size == other.countCols() - 1)
        {
            Point<size, T> result;
            for (int i = 0; i < size; i++)
            {
                result[i] = 0;
                for (int j = 0; j < size; j++)
                {
                    result[i] += (*this)[j] * other[j][i];
                }
                result[i] += other[size][i];
            }
            return result;
        }
        throw ("Index out of range");

    }
}
#endif // POINT_HPP
