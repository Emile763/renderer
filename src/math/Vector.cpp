
#include "Vector.h"
#include <cassert>
#include <cmath>
template <unsigned int n, typename T>
Vector<n, T>::Vector() : m_data{ 0 } {}

template <unsigned int n, typename T>
Vector<n, T>::Vector(std::initializer_list<T> params)
{
    std::copy(params.begin(), params.end(), m_data.begin());
}

template <unsigned int n, typename T>
unsigned int Vector<n, T>::getSize() {
    return n;
}

template <unsigned int n, typename T>
const T* Vector<n, T>::getData() const {
    return m_data.data();
}

template <unsigned int n, typename T>
float Vector<n, T>::getModulus(){
    float squared_sum = 0;
    for(unsigned int i = 0; i < n; i++){
        squared_sum += std::powf((*this)[i], 2);
    }
    return std::sqrtf(squared_sum);
}

template<unsigned int n, typename T>
Vector<n, T> Vector<n, T>::operator*(const float& x) const
{
    Vector<n, T> result = *this;

    for(unsigned int i = 0; i < n; i++){
        result[i] *= x;
    }
    return result;
}
template<unsigned int n, typename T>
Vector<n, T> Vector<n, T>::operator+(const Vector<n, T>& other) const
{
    Vector<n, T> result = *this;
    return result += other;
}

template<unsigned int n, typename T>
Vector<n, T>& Vector<n, T>::operator+=(const Vector<n, T>& other)
{
    for(unsigned int i = 0; i < n; i++){
        (*this)[i] += other[i];
    }
    return *this;
}

template<unsigned int n, typename T>
Vector<n, T> Vector<n, T>::operator-(const Vector<n,T>& other) const {
    return *this + -other;
}

template<unsigned int n, typename T>
Vector<n, T>& Vector<n, T>::operator-=(const Vector<n, T>& other)
{
    *this += -other; 
    return *this;
}

template <unsigned int n, typename T>
Vector<n,T>& Vector<n, T>::normalize(){
    float modulus = this->getModulus();
    if(modulus >= std::numeric_limits<float>::epsilon()){
        for(unsigned int i = 0; i < n; i++){
            (*this)[i] /= modulus;
        }
    }

    return *this;
}
template <unsigned int n, typename T>
Vector<n, T> Vector<n, T>::getNormalized(){
    Vector<n, T> result = *this;
    return result.normalize();
}

template <unsigned int n, typename T>
T& Vector<n, T>::operator[](const unsigned int& i) {
    return m_data[i];
}

template <unsigned int n, typename T>
const T& Vector<n, T>::operator[](const unsigned int& i) const {
    return m_data[i];
}

template <unsigned int n, typename T>
Vector<n, T> Vector<n, T>::operator-() const {
    Vector<n, T> result;
    for (unsigned int i = 0; i < n; i++)
        result[i] = -(*this)[i];

    return result;
}
