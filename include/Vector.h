#pragma once
#include <initializer_list>
#include <array>

template <unsigned int n, typename T = float>
class Vector {
private:
    std::array<T, n> m_data;
public:
    Vector();
    Vector(std::initializer_list<T> params);

    unsigned int getSize();
    const T* getData() const;

    Vector<n,T>& normalize();
    Vector<n, T> getNormalized();
    float getModulus();

    T& operator[](const unsigned int& i);
    const T& operator[](const unsigned int& i) const;
    Vector<n, T> operator*(const float& x) const;
    Vector<n, T> operator+(const Vector<n,T>& other) const;
    

    Vector<n, T> operator-() const;
};



template class Vector<2>;
typedef Vector<2> Vec2;

template class Vector<3>;
typedef Vector<3> Vec3;

template class Vector<4>;
typedef Vector<4> Vec4;

