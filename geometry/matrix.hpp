#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix.h"

namespace GeometrySpace
{
    template <typename T>
    Matrix<T>::Matrix(const int &rows, const int &cols)
        : _rows(rows), _cols(cols)
    {
        try
        {
            data = new T* [_rows];
            for (int i = 0; i < _rows; i++)
            {
                data[i] = new T[_cols];
                for (int j = 0; j < _cols; j++)
                    data[i][j] = 0;
            }
        }
        catch (std::bad_alloc)
        {
            throw "Matrix allocation error";
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const MathVector<T> &other)
        : _rows(other.size()), _cols(1)
    {
        try
        {
            data = new T* [_rows];
            for (int i = 0; i < _rows; i++)
            {
                data[i] = new T[_cols];
                data[i][0] = other[i];
            }
        }
        catch (std::bad_alloc)
        {
            throw "Matrix allocation error";
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &other)
        : _rows(other.countRows()), _cols(other.countCols())
    {
        try
        {
            data = new T* [_rows];
            for (int i = 0; i < _rows; i++)
            {
                data[i] = new T[_cols];
                for (int j = 0; j < _cols; j++)
                    data[i][j] = other[i][j];
            }
        }
        catch (std::bad_alloc)
        {
            throw "Matrix allocation error";
        }
    }

    template <typename T>
    Matrix<T>::~Matrix()
    {
        for (int i = 0; i < _rows; i++)
        {
            delete [] data[i];
        }
        delete [] data;
    }


    template <typename T>
    void Matrix<T>::makeIdentity()
    {
        if (_rows == _cols)
        {
            for (int i = 0; i < _rows; i++)
            {
                for (int j = 0; j < _cols; j++)
                {
                    if (i == j)
                        data[i][j] = 1;
                    else
                        data[i][j] = 0;
                }
            }
        }
        else
            throw "Not a square matrix";
    }

    template <typename T>
    T* Matrix<T>::operator [] (int index)
    {
        if (index < _rows)
            return data[index];
        else
            throw std::out_of_range("Index out of range");
    }

    template <typename T>
    const T* Matrix<T>::operator [] (const int &index) const
    {
        if (index < _rows)
            return data[index];
        else
            throw std::out_of_range("Index out of range");
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator * (const Matrix &other)
    {
        if (_cols == other.countRows())
        {
            Matrix result(_rows, _cols);
            for (int i = 0; i < _rows; i++)
            {
                for (int j = 0; j < other.countCols(); j++)
                {
                    for (int k = 0; k < _cols; k++)
                    {
                        result[i][j] += (*this)[i][k] * other[k][j];
                    }
                }
            }
            return result;
        }
        else
            throw "Incompatible sizes of the matrices";
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator + (const Matrix &other)
    {
        if (_cols == other.countCols() && _rows == other.countRows())
        {
            Matrix result(*this);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    result[i][j] += other[i][j];
            return result;
        }
        else
            throw "Incompatible sizes of the matrices";
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator - (const Matrix &other)
    {
        if (_cols == other.countCols() && _rows == other.countRows())
        {
            Matrix result(*this);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    result[i][j] -= other[i][j];
            return result;
        }
        else
            throw "Incompatible sizes of the matrices";
    }

    template <typename T>
    Matrix<T> Matrix<T>::getTranspose()
    {
        Matrix result(_cols, _rows);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                result[j][i] = (*this)[i][j];
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::getInverse()
    {
        if (_rows == _cols)
        {
            // Getting (A | E) Matrix
            Matrix result(_rows, _cols * 2);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    result[i][j] = (*this)[i][j];
            for (int i = 0; i < _rows; i++)
                result[i][i + _cols] = 1;

            // Zeroing lower triangle
            for (int i = 0; i < _rows - 1; i++)
            {
                for (int j = result.countCols() - 1; j >= 0; j--)
                    result[i][j] /= result[i][i];
                for (int k = i + 1; k < _rows; k++)
                {
                    double coef = result[k][i];
                    for (int j = 0; j < result.countCols(); j++)
                        result[k][j] -= result[i][j] * coef;
                }
            }

            // Zeroing upper triangle
            for (int j = result.countCols() - 1; j >= _rows - 1; j--)
                result[_rows - 1][j] /= result[_rows - 1][_rows - 1];

            for (int i = _rows - 1; i > 0; i--)
            {
                for (int k = i - 1; k >= 0; k--)
                {
                    double coef = result[k][i];
                    for (int j = k + 2; j < result.countCols(); j++)
                        result[k][j] -= result[i][j] * coef;
                }
            }

            Matrix inverse(_rows, _cols);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    inverse[i][j] = result[i][j + _cols];
            return inverse;
        }
        else
            throw "Not a square matrix";
    }

}


#endif // MATRIX_HPP
