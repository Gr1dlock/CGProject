#ifndef MATRIX_H
#define MATRIX_H

#include "geometry.h"

namespace GeometrySpace
{
    template <typename T>
    class Matrix
    {

    private:
        T **data;
        int _rows, _cols;

    public:
        Matrix();
        Matrix(const int &rows, const int &cols);
        Matrix(const Matrix<T> &other);
        Matrix(const MathVector<T> &other);
        ~Matrix();
        int countRows() const { return _rows; }
        int countCols() const { return _cols; }
        void makeIdentity();
        T* operator [] (int index);
        const T* operator [] (const int &index) const;
        Matrix<T> operator * (const Matrix &other);
        MathVector<T> operator * (const MathVector<T> &other);
        Matrix<T> operator + (const Matrix &other);
        Matrix<T> operator - (const Matrix &other);
        Matrix<T> getTranspose();
        Matrix<T> getInverse();
    };
}
#endif // MATRIX_H
