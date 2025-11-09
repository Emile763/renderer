#include "Movable2D.h"
#include "MatrixUtils.h"
Movable2D::Movable2D()
    : m_rotation(0.f), m_translation_matrix(Mat3::Identity()), m_rotation_matrix(), m_scale_matrix(Mat3::Identity()), m_size(1.f)
{
    setRotation(m_rotation);
}

Vec2 Movable2D::getPosition() const {
    return Vec2{ m_translation_matrix[0][2], m_translation_matrix[1][2] };
}
float Movable2D::getRotation() const {
    return m_rotation;
}
Vec2 Movable2D::getScale() const {
    return Vec2{ m_translation_matrix[0][0], m_translation_matrix[1][1] };
}

void Movable2D::setPosition(const Vec2& new_position) {
    m_translation_matrix[0][2] = new_position[0];
    m_translation_matrix[1][2] = new_position[1];
}
void Movable2D::setRotation(const float& new_rotation) {
    m_rotation = new_rotation;
    m_rotation_matrix = Get2DRotationMatrix(m_rotation);

}
void Movable2D::setScale(const Vec2& new_scale) {
    m_scale_matrix[0][0] = new_scale[0];
    m_scale_matrix[1][1] = new_scale[1];
}

void Movable2D::setSize(const float& size)
{
    m_size = size;
}




