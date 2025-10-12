#include "Object3D.h"
#include "Shader.h"
#include "MatrixUtils.h"
#include "ShaderUtils.h"
Object3D::Object3D() : Movable3D()
{
}



void Object3D::setShaderVariables() const {
    Shader::setMat4(ShaderVarLocations::TRANSLATION_MATRIX, m_translation_matrix);
    Shader::setMat4(ShaderVarLocations::ROTATION_MATRIX, m_rotation_matrix);
    Shader::setMat4(ShaderVarLocations::SCALE_MATRIX, m_scale_matrix);
}