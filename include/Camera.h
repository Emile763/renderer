#pragma once
#include "Object.h"
#include "Movable3D.h"
#include "Matrix.h"
class Camera : public Object, public Movable3D
{
private:
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;
    float m_vertical_fov;
    Mat4 m_projection_matrix;
public:
    // near plane position; far plane position; vertical field of view in degree
    Camera(const float& aspect_ratio, const float& near, const float& far, const float& fov);
    virtual void setShaderVariables() const override;

    void LookAt(const Vec3& position);
};
