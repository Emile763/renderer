#pragma once
#include "IObject.h"
#include "Movable3D.h"
class Object3D : public IObject, public Movable3D
{
public:
    Object3D();
    virtual void setShaderVariables() const override;
};
