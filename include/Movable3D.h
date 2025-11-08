#pragma once
#include <Vector.h>
#include <Matrix.h>

class Movable3D
{
protected:
    Vec3 m_rotation;

    Mat4 m_translation_matrix;
    Mat4 m_rotation_matrix;
    Mat4 m_scale_matrix;    

    Movable3D();

public:

    virtual Vec3 getPosition() const;
    virtual Vec3 getRotation() const;
    virtual Vec3 getScale() const;

    virtual void setPosition(const Vec3& new_position);
    virtual void setRotation(const Vec3& new_rotation);
    virtual void setScale(const Vec3& new_scale);

};

