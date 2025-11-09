#include "EmptyShaderParameter.h"

EmptyShaderParameter* EmptyShaderParameter::m_singleton = nullptr;


const EmptyShaderParameter& EmptyShaderParameter::getIntance()
{
    if(m_singleton == nullptr)
        m_singleton = new EmptyShaderParameter;
    return *m_singleton;
}

void EmptyShaderParameter::deleteInstance()
{
    if(m_singleton != nullptr)
    {
        delete m_singleton;
        m_singleton = nullptr;
    }
}

