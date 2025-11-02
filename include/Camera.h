#pragma once
#include "IShaderParameter.h"
#include "Movable3D.h"
#include "Matrix.h"
class Camera : public IShaderParameter, public Movable3D
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
    virtual void setShaderParameters() const override;

    void setPosition(const Vec3& new_position) override;
    void setRotation(const Vec3& new_rotation) override;
    
    const Vec3 getPosition() const override;
    const Vec3 getRotation() const override;
    
    void LookAt(const Vec3& position);

    Vec3 getDirection();
};
