#include "Object2D.h"
#include "Shader.h"
#include "MatrixUtils.h"
#include "ShaderUtils.h"
Object2D::Object2D() : Movable2D()
{
}



void Object2D::setShaderParameters() const {
    Shader::setMat3(ShaderVarLocations::TRANSLATION_MATRIX, m_translation_matrix);
    Shader::setMat3(ShaderVarLocations::ROTATION_MATRIX, m_rotation_matrix);
    Shader::setMat3(ShaderVarLocations::SCALE_MATRIX,  m_size * m_scale_matrix);
}