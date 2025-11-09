#pragma once
class IShaderParameter {
public:
    virtual ~IShaderParameter() = default;


    virtual void setShaderParameters() const = 0;
};