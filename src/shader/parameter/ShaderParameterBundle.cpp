#include "ShaderParameterBundle.h"

ShaderParameterBundle::ShaderParameterBundle() {}

void ShaderParameterBundle::add(const IShaderParameter& parameter)
{
    m_parameters.insert(&parameter);
}

void ShaderParameterBundle::remove(const IShaderParameter& parameter)
{
    m_parameters.erase(&parameter);
}

void ShaderParameterBundle::clear()
{
    m_parameters.clear();
}

void ShaderParameterBundle::setShaderParameters() const
{
    for(const IShaderParameter* param : m_parameters){
        param->setShaderParameters();
    }
}
