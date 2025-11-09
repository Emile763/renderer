#pragma once
#include "IShaderParameter.h"
#include "Movable2D.h"
class Object2D : public IShaderParameter, public Movable2D
{
public:
    Object2D();
    virtual void setShaderParameters() const override;
};
