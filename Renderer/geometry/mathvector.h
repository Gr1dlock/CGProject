#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include "geometry.h"
#include <iostream>

namespace GeometrySpace
{
    template <typename T>
    class MathVector
    {
    private:
        int length;
        T *data;
    public:
        MathVector();
        MathVector(const int &count);
        MathVector(const T &x, const T &y, const T &z);
        MathVector(const T &x, const T &y, const T &z, const T &w);
        MathVector(const MathVector<T> &other);
        MathVector(std::initializer_list <T> list);
        template <int size_T>
        MathVector(const Point<size_T, T> &point);

        ~MathVector();

        template <int size_T>
        MathVector<T> &operator = (const Point<size_T, T> &point);
        MathVector<T> &operator = (const MathVector<T> &other);
        MathVector<T> &operator = (std::initializer_list <T> list);

        MathVector<T> operator + (const MathVector<T> &other) const;
        MathVector<T> operator - (const MathVector<T> &other) const;
        MathVector<T> operator * (double f) const;
        T operator * (const MathVector<T>& other) const;
        MathVector<T> operator ^ (const MathVector<T>& other) const;
        T &operator [] (int index);
        const T &operator [] (const int &index) const;

        double module() const;
        void normalise();

        int size() const { return length; }
    };
}
#endif // MATHVECTOR_H
