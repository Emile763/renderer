#include "ShaderTextureParameter.h"
#include "Shader.h"
GLenum ShaderTextureParameter::current_texture_unit = GL_TEXTURE0;

void ShaderTextureParameter::nextTextureUnit()
{
    current_texture_unit = ((current_texture_unit - GL_TEXTURE0) + 1) % 10 + GL_TEXTURE0;
}

ShaderTextureParameter::ShaderTextureParameter(Texture& texture, const TextureLocations& channel) : m_texture(texture), m_channel(channel) {}



void ShaderTextureParameter::setShaderParameters() const
{
    glActiveTexture(current_texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_texture.getTextureId());
    Shader::setInt((ShaderVarLocations)m_channel, current_texture_unit - GL_TEXTURE0);
}
