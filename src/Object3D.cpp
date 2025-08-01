#include "Object3D.h"
#include "Shader.h"
#include "MatrixUtils.h"
#include "ShaderUtils.h"
Object3D::Object3D() : Movable3D()
{
}



void Object3D::setShaderVariables() const {
    Mat4 translation = Get3DTranslationMatrix(m_position);
    Mat4 rotation = Get3DRotationMatrix(m_rotation);
    Mat4 scale = Get3DScaleMatrix(m_scale);

    Shader::setMat4(ShaderVarLocations::TRANSLATION_MATRIX, translation);
    Shader::setMat4(ShaderVarLocations::ROTATION_MATRIX, rotation);
    Shader::setMat4(ShaderVarLocations::SCALE_MATRIX, scale);
}