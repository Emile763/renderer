#pragma once
#include "Texture.h"
#include "ShaderUtils.h"
#include "IShaderParameter.h"
class ShaderTextureParameter : public IShaderParameter
{
private:
    static GLenum current_texture_unit;
    static void nextTextureUnit();

    Texture& m_texture;
    TextureLocations m_channel;
public:
    ShaderTextureParameter(Texture &texture, const TextureLocations &channel = TextureLocations::TEXTURE_0);

    void setShaderParameters() const override;
};
