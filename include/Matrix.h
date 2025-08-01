#pragma once
#include "Vector.h"
template <unsigned int n, unsigned int m, typename T = float>
class Matrix {
private:
    std::array<T, n * m> m_data;
public:
    typedef Vector<m> Column;
    typedef Vector<n> Line;
    Matrix();
    Matrix(std::initializer_list<T> params);

    unsigned int getWidth();
    unsigned int getHeight();
    const T* getData() const;

    Column& operator[](const unsigned int& i);
    const Column& operator[](const unsigned int& i) const;

    template <unsigned int n2>
    Matrix<n2, m, T> operator*(const Matrix<n2, n, T>& other);
};

template <unsigned int n, unsigned int m, typename T>
template<unsigned int n2>
inline Matrix<n2, m, T> Matrix<n, m, T>::operator*(const Matrix<n2, n, T>& other)
{
    Matrix<n2, m, T> result;
    for (unsigned int i = 0; i < n2; i++)
        for (unsigned int j = 0; j < m; j++)
            for (unsigned int k = 0; k < n; k++)
                result[i][j] += (*this)[i][k] * other[k][j];
    return result;
}

template class Matrix<2, 2>;
typedef Matrix<2, 2> Mat2;

typedef Matrix<3, 3> Mat3;
template class Matrix<3, 3>;

template class Matrix<4, 4>;
typedef Matrix<4, 4> Mat4;




