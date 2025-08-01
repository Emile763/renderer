#pragma once
#include <Vector.h>

class Movable3D
{
protected:
    Vec3 m_position;
    Vec3 m_rotation;
    Vec3 m_scale;
    Movable3D();
public:

    virtual const Vec3& getPosition() const;
    virtual const Vec3& getRotation() const;
    virtual const Vec3& getScale() const;

    virtual void setPosition(Vec3&& new_position);
    virtual void setRotation(Vec3&& new_rotation);
    virtual void setScale(Vec3&& new_scale);
};

