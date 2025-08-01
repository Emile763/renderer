#include "Camera.h"
#include "MatrixUtils.h"
#include <cmath>
#include <iostream>
#include <Shader.h>
constexpr float PI = 3.1415926;
Mat4 GetProjectionMatrix(const float& aspect_ratio, const float& near, const float& far, const float& fov) {
    float fov_rad = PI * fov / 180.f;
    float inv_tan = 1.f / std::tanf(fov_rad / 2);

    return  {
        inv_tan / aspect_ratio, 0.f , 0.f, 0.f,
        0.f,    inv_tan, 0.f, 0.f,
        0.f,    0.f   , -(far + near) / (far - near), -2.f * far * near / (far - near),
        0.f,    0.f   , -1.f, 0.f
    };
}

Camera::Camera(const float& aspect_ratio, const float& near, const float& far, const float& fov)
    : Movable3D(), m_aspect_ratio(aspect_ratio),
    m_near_plane(near), m_far_plane(far), m_vertical_fov(fov),
    m_projection_matrix(GetProjectionMatrix(aspect_ratio, near, far, fov))
{

}



void Camera::setShaderVariables() const {
    Mat4 view_matrix = Get3DRotationMatrix(-m_rotation) * Get3DTranslationMatrix(-m_position);
    
    Shader::setMat4(ShaderVarLocations::VIEW_MATRIX, view_matrix);
    Shader::setMat4(ShaderVarLocations::PROJECTION_MATRIX, m_projection_matrix);
}

void Camera::LookAt(const Vec3& position)
{
    // m_rotation[0] = atan2(position[2] - m_position[2], position[0] - m_position[0]);
    m_rotation[1] = std::atan2f(m_position[0] - position[0], m_position[2] - position[2]);
    // std::cout << m_rotation[1] * 180.f / 3.1415926f << "\n";
    // m_rotation[2] = atan2(position[2] - m_position[2], position[1] - m_position[1]);
}
