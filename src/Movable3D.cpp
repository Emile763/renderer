#include "Movable3D.h"

Movable3D::Movable3D()
    : m_position{ 0.f,0.f,0.f }, m_rotation{ 0.f,0.f,0.f }, m_scale{ 1.f,1.f,1.f }
{
}

const Vec3& Movable3D::getPosition() const {
    return m_position;
}
const Vec3& Movable3D::getRotation() const {
    return m_rotation;
}
const Vec3& Movable3D::getScale() const {
    return m_scale;
}

void Movable3D::setPosition(Vec3&& new_position) {
    m_position = new_position;
}
void Movable3D::setRotation(Vec3&& new_rotation) {
    m_rotation = new_rotation;
}
void Movable3D::setScale(Vec3&& new_scale) {
    m_scale = new_scale;
}
