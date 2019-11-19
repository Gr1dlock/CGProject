#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include "mathvector.h"


namespace GeometrySpace
{
    template <typename T>
    MathVector<T>::MathVector()
        : length(0)
    {
        data = nullptr;
    }

    template <typename T>
    MathVector<T>::MathVector(const int &count)
        : length(count)
    {
        try
        {
            data = new T[length];
        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template<typename T>
    MathVector<T>::MathVector(const T &x, const T &y, const T &z, const T &w)
    {
        try
        {
                length = 4;
                data = new T[length];
                data[0] = x;
                data[1] = y;
                data[2] = z;
                data[3] = w;

        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template<typename T>
    MathVector<T>::MathVector(const T &x, const T &y, const T &z)
    {
        try
        {
                length = 3;
                data = new T[length];
                data[0] = x;
                data[1] = y;
                data[2] = z;

        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template <typename T>
    MathVector<T>::MathVector(const MathVector<T>& other):
        length(other.size())
    {
        try
        {
            data = new T[length];
            memcpy(data, other.data, length * sizeof(T));
        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template <typename T>
    MathVector<T>::MathVector(std::initializer_list<T> list):
        length(list.size())
    {
        try
        {
            data = new T[length];
            size_t i = 0;
            for (const auto &el: list)
            {
                data[i] = el;
                i++;
            }
        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template <typename T>
    MathVector<T> &MathVector<T>::operator = (const MathVector<T>& other)
    {
        if (this == &other) return *this;
        try
        {
            if (other.size() != length)
            {
                delete [] data;
                length = other.length;
                data =new T[length];
            }
            memcpy(data, other.data, length * sizeof(T));
        }
        catch(std::bad_alloc)
        {
            throw "Allocation error";
        }
        return *this;
    }

    template <typename T>
    template <int size_T>
    MathVector<T> &MathVector<T>::operator = (const Point<size_T, T> &other)
    {
        try
        {
            if (size_T != length)
            {
                delete [] data;
                length = size_T;
                data = new T[length];
            }
            for (int i = 0; i < size_T; i++)
                data[i] = other[i];
        }
        catch(std::bad_alloc)
        {
            throw "Allocation error";
        }
        return *this;
    }

    template <typename T>
    MathVector<T> &MathVector<T>::operator = (std::initializer_list<T> list)
    {
        try
        {
            if (length != list.size())
            {
                delete [] data;
                length = list.size();
                data = new T[length];
            }
            for (int i = 0; i < length; i++)
                data[i] = list[i];
        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
        return *this;
    }

    template <typename T>
    MathVector<T>::~MathVector()
    {
        delete [] data;
    }

    template<typename T>
    MathVector<T> MathVector<T>::operator + (const MathVector<T> &v) const
    {
        MathVector result(*this);
        for (int i = 0; i < 3; i++)
            result[i] += v[i];
        return result;
    }

    template<typename T>
    MathVector<T> MathVector<T>::operator - (const MathVector<T> &v) const
    {
        MathVector result(*this);
        for (int i = 0; i < 3; i++)
            result[i] -= v[i];
        return result;
    }

    template<typename T>
    MathVector<T> MathVector<T>::operator *(double f) const
    {
        MathVector result(*this);
        for (int i = 0; i < 3; i++)
            result[i] *= f;
        return result;
    }

    template<typename T>
    T &MathVector<T>::operator [](int index)
    {
        if (index < length)
        {
            return data[index];
        }


        throw std::out_of_range("Index out of range");
    }

    template<typename T>
    const T &MathVector<T>::operator [](const int &index) const
    {
        if (index < length)
        {
            return data[index];
        }


        throw std::out_of_range("Index out of range");
    }

    template<typename T>
    T MathVector<T>::operator *(const MathVector<T> &other) const
    {
        T result = 0;
        for (int i = 0; i < 3; i++)
            result += data[i] * other[i];
        return result;
    }

    template <typename T>
    MathVector<T> MathVector<T>::operator ^ (const MathVector<T>& other) const
    {
        MathVector result(*this);
        result[0] = data[1] * other[2] - data[2] * other[1];
        result[1] = data[2] * other[0] - data[0] * other[2];
        result[2] = data[0] * other[1] - data[1] * other[0];
        return result;
    }

    template <typename T>
    template <int size_T>
    MathVector<T>::MathVector(const Point<size_T, T> &other)
        : length(size_T)
    {
        try
        {
            data = new T[length];
            for (int i = 0; i < size_T; i++)
                data[i] = other[i];
        }
        catch (std::bad_alloc)
        {
            throw "Allocation error";
        }
    }

    template <typename T>
    double MathVector<T>::module() const
    {
        double res = 0;
        for (int i = 0; i < 3; i++)
        {
            res += data[i] * (*this)[i];
        }
        return sqrt(res);
    }

    template <typename T>
    void MathVector<T>::normalize()
    {
        double mod = module();
        for (int i = 0; i < 3; i++)
        {
            data[i] /= mod;
        }
    }

    template<typename T>
    MathVector<T> MathVector<T>::operator * (const Matrix<T> &other) const
    {
        if ((length == other.countRows() && length == other.countCols()) ||
                (length == other.countRows() - 1 && length == other.countCols() - 1))
        {
            MathVector<T> result(length);
            for (int i = 0; i < length; i++)
            {
                result[i] = 0;
                for (int j = 0; j < length; j++)
                {
                    result[i] += data[j] * other[j][i];
                }
            }
            return result;
        }
        throw("Invalid matrix size");
    }

    template <typename T>
    template <int size_T>
    T MathVector<T>::operator * (const Point<size_T, T> &other) const
    {
        T result = 0;
        for (int i = 0; i < size_T; i++)
        {
            result += data[i] * other[i];
        }
        return result;
    }
}

#endif // MATHVECTOR_HPP
