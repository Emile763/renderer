#pragma once
#include "IShaderParameter.h"
#include "Movable2D.h"
#include "Matrix.h"
class Camera2D : public IShaderParameter, public Movable2D
{
private:
    float m_aspect_ratio;
    float m_vertical_fov;
    Mat3 m_projection_matrix;
public:

    Camera2D(const float& aspect_ratio);
    virtual void setShaderParameters() const override;

    void setPosition(const Vec2& new_position) override;
    
    Vec2 getPosition() const override;

};
