#pragma once
#include "IShaderParameter.h"
#include "Movable3D.h"
class Object3D : public IShaderParameter, public Movable3D
{
public:
    Object3D();
    virtual void setShaderParameters() const override;
};
