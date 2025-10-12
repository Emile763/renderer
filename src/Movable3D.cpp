#include "Movable3D.h"
#include "MatrixUtils.h"
Movable3D::Movable3D()
    : m_translation_matrix{Identity}, m_rotation{ 0.f,0.f,0.f }, m_scale_matrix{Identity}
{
    setRotation(m_rotation);
}

const Vec3 Movable3D::getPosition() const {
    return Vec3{m_translation_matrix[0][3], m_translation_matrix[1][3], m_translation_matrix[2][3]};
}
const Vec3 Movable3D::getRotation() const {
    return m_rotation;
}
const Vec3 Movable3D::getScale() const {
    return Vec3{m_translation_matrix[0][0], m_translation_matrix[1][1], m_translation_matrix[2][2]};
}

void Movable3D::setPosition(const Vec3& new_position) {
    m_translation_matrix[0][3] = new_position[0];
    m_translation_matrix[1][3] = new_position[1]; 
    m_translation_matrix[2][3] = new_position[2]; 
}
void Movable3D::setRotation(const Vec3& new_rotation) {
    m_rotation = new_rotation;
    m_rotation_matrix = Get3DRotationMatrix(m_rotation);

}
void Movable3D::setScale(const Vec3& new_scale) {
    m_scale_matrix[0][0] = new_scale[0];
    m_scale_matrix[1][1] = new_scale[1]; 
    m_scale_matrix[2][2] = new_scale[2]; 
}

