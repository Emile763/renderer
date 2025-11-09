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

    inline Column& operator[](const unsigned int& i);
    inline const Column& operator[](const unsigned int& i) const;

    template <unsigned int n2>
    Matrix<n2, m, T> operator*(const Matrix<n2, n, T>& other) const;
    
    Vector<m, T> operator*(const Vector<n, T>& other) const; 

    static Matrix<n,m,T> Identity();
};

template <unsigned int n, unsigned int m, typename T>
Matrix<n, m, T>::Matrix() :m_data{ T(0) } {}

template <unsigned int n, unsigned int m, typename T>
Matrix<n, m, T>::Matrix(std::initializer_list<T> params) {
    std::copy(params.begin(), params.end(), m_data.begin());
}

template <unsigned int n, unsigned int m, typename T>
unsigned int Matrix<n, m, T>::getWidth() {
    return n;
}
template <unsigned int n, unsigned int m, typename T>
unsigned int Matrix<n, m, T>::getHeight() {
    return m;
}

template <unsigned int n, unsigned int m, typename T>
const T* Matrix<n, m, T>::getData() const {
    return m_data.data();
}

template<unsigned int n, unsigned int m, typename T>
inline Vector<m>& Matrix<n, m, T>::operator[](const unsigned int& i)
{
    return *(Vector<m>*) & m_data[n * i];
}

template<unsigned int n, unsigned int m, typename T>
inline const Vector<m>& Matrix<n, m, T>::operator[](const unsigned int& i) const
{
    return *(Vector<m>*)(&m_data[n * i]);
}

template<unsigned int n, unsigned int m, typename T>
Vector<m, T> Matrix<n, m, T>::operator*(const Vector<n, T>& other) const{
    Vector<m,T> result;
    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int k = 0; k < n; k++)
        {
            result[i] += other[k] * (*this)[k][i];
        }
    }
    return result;    
}

template <unsigned int n, unsigned int m, typename T>
template<unsigned int n2>
inline Matrix<n2, m, T> Matrix<n, m, T>::operator*(const Matrix<n2, n, T>& other) const
{
    Matrix<n2, m, T> result;
    for (unsigned int i = 0; i < n2; i++)
        for (unsigned int j = 0; j < m; j++)
            for (unsigned int k = 0; k < n; k++)
                result[i][j] += (*this)[i][k] * other[k][j];
    return result;
}

template<unsigned int n, unsigned int m, typename T>
inline Matrix<n, m, T> Matrix<n, m, T>::Identity()
{
    Matrix<n,m,T> result;
    for(unsigned int i = 0; i < n && i < m; i++){
        result[i][i] = 1;
    }
    return result;
}
template <unsigned int n, unsigned int m, typename T>
inline Matrix<n, m, T> operator*(const float& x, const Matrix<n, m, T>& other)
{
    Matrix<n, m, T> result;
    for (unsigned int i = 0; i < n; i++)
        for (unsigned int j = 0; j < m; j++)
            result[i][j] = x * other[i][j];
    return result;
}


template class Matrix<2, 2>;
typedef Matrix<2, 2> Mat2;

typedef Matrix<3, 3> Mat3;
template class Matrix<3, 3>;

template class Matrix<4, 4>;
typedef Matrix<4, 4> Mat4;


