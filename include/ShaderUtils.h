#pragma once

enum class ShaderVarLocations{
    POSITION           = 0,
    NORMAL             = 1,
    TEXTURE_COORD      = 2,
    COLOR              = 3,

    PROJECTION_MATRIX  = 4,
    TRANSLATION_MATRIX = 5,
    ROTATION_MATRIX    = 6,
    SCALE_MATRIX       = 7,
    VIEW_MATRIX        = 8,

    CAMERA_POS         = 9,
    TIME               = 10,




    TEXTURE_0 = 40,
    TEXTURE_1 = 41,
    TEXTURE_2 = 42,
    TEXTURE_3 = 43,
    TEXTURE_4 = 44,
    TEXTURE_5 = 45,
    TEXTURE_6 = 46,
    TEXTURE_7 = 47,
    TEXTURE_8 = 48,
    TEXTURE_9 = 49,

};


enum class TextureLocations{
    TEXTURE_0 = (int)ShaderVarLocations::TEXTURE_0,
    TEXTURE_1 = (int)ShaderVarLocations::TEXTURE_1,
    TEXTURE_2 = (int)ShaderVarLocations::TEXTURE_2,
    TEXTURE_3 = (int)ShaderVarLocations::TEXTURE_3,
    TEXTURE_4 = (int)ShaderVarLocations::TEXTURE_4,
    TEXTURE_5 = (int)ShaderVarLocations::TEXTURE_5,
    TEXTURE_6 = (int)ShaderVarLocations::TEXTURE_6,
    TEXTURE_7 = (int)ShaderVarLocations::TEXTURE_7,
    TEXTURE_8 = (int)ShaderVarLocations::TEXTURE_8,
    TEXTURE_9 = (int)ShaderVarLocations::TEXTURE_9,
};