#pragma once
#include "Object.h"
#include "Movable3D.h"
class Object3D : public Object, public Movable3D
{
public:
    Object3D();
    virtual void setShaderVariables() const override;
};
