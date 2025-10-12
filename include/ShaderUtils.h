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

};