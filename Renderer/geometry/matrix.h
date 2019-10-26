#ifndef MATRIX_H
#define MATRIX_H

#include "geometry.h"
#include <iostream>

namespace GeometrySpace
{
    template <typename T>
    class Matrix
    {

    private:
        T **data;
        int _rows, _cols;

    public:
        Matrix(const int &rows, const int &cols);
        Matrix(const Matrix<T> &other);
        Matrix(const MathVector<T> &other);
        ~Matrix();
        inline int countRows() const { return _rows; }
        inline int countCols() const { return _cols; }
        void makeIdentity();
        T* operator [] (int index);
        const T* operator [] (const int &index) const;
        Matrix<T> operator * (const Matrix &other);
        Matrix<T> operator * (const Matrix &other) const;
        Matrix<T> operator + (const Matrix &other);
        Matrix<T> operator - (const Matrix &other);
        Matrix<T> operator = (const Matrix &other);
        Matrix<T> getTranspose();
        Matrix<T> getInverse();
        bool isZero();
    };
}
#endif // MATRIX_H