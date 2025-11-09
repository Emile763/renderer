#include "Camera2D.h"
#include "MatrixUtils.h"
#include <cmath>
#include <iostream>
#include <Shader.h>

Mat3 GetProjectionMatrix(const float& aspect_ratio) {
    return  {
        1.f/aspect_ratio, 0.f, 0.f,
        0.f,          1.f, 0.f,
        0.f,          0.f, 1.f
    };
}

Camera2D::Camera2D(const float& aspect_ratio)
    : Movable2D(), m_aspect_ratio(aspect_ratio),
    m_projection_matrix(GetProjectionMatrix(aspect_ratio)) {}

void Camera2D::setPosition(const Vec2& new_position) {
    Movable2D::setPosition(-new_position);
}

Vec2 Camera2D::getPosition() const{
    return -Movable2D::getPosition();
}

void Camera2D::setShaderParameters() const {
    
    Mat3 view_matrix = m_rotation_matrix * m_translation_matrix;
    
    Shader::setMat3(ShaderVarLocations::VIEW_MATRIX, view_matrix);
    Shader::setMat3(ShaderVarLocations::PROJECTION_MATRIX, m_projection_matrix);
}
