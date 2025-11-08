#pragma once
#include <Vector.h>
#include <Matrix.h>

class Movable2D
{
protected:
    float m_rotation;

    Mat3 m_translation_matrix;
    Mat3 m_rotation_matrix;
    Mat3 m_scale_matrix;    

    float m_size;
    
    Movable2D();

public:

    virtual Vec2 getPosition() const;
    virtual float getRotation() const;
    virtual Vec2 getScale() const;

    virtual void setPosition(const Vec2& new_position);
    virtual void setRotation(const float& new_rotation);
    virtual void setScale(const Vec2& new_scale);

    virtual void setSize(const float& size);
};

