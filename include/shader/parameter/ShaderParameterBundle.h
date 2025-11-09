#pragma once
#include "IShaderParameter.h"
#include <unordered_set>

class ShaderParameterBundle : public IShaderParameter
{
private:
    // Better containers ?
    std::unordered_set<const IShaderParameter*> m_parameters;

public:
    ShaderParameterBundle();

    void add(const IShaderParameter& parameter);
    void remove(const IShaderParameter& parameter);
    void clear();

    void setShaderParameters() const override;
};

