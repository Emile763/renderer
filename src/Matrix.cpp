#include "Matrix.h"


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
Vector<m>& Matrix<n, m, T>::operator[](const unsigned int& i)
{
    return *(Vector<m>*) & m_data[n * i];
}

template<unsigned int n, unsigned int m, typename T>
const Vector<m>& Matrix<n, m, T>::operator[](const unsigned int& i) const
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