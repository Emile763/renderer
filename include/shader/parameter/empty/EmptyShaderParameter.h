#pragma once
#include "IShaderParameter.h"
class EmptyShaderParameter : public IShaderParameter
{
private:
    static EmptyShaderParameter* m_singleton;
    EmptyShaderParameter() {};
public:
    EmptyShaderParameter(EmptyShaderParameter&) = delete;
    void operator=(const EmptyShaderParameter&) = delete;

    void setShaderParameters() const override {};

    static const EmptyShaderParameter& getIntance();
    static void deleteInstance();
};
