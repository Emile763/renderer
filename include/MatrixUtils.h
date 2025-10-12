#pragma once
#include "Vector.h"
#include "Matrix.h"

const Mat4 Identity{
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};

Mat4 Get3DXRotationMatrix(const float& angle);
Mat4 Get3DYRotationMatrix(const float& angle);
Mat4 Get3DZRotationMatrix(const float& angle);

Mat4 Get3DTranslationMatrix(const Vec3& position);
Mat4 GetEulerRotationMatrix(const Vec3& rotation);
Mat4 Get3DRotationMatrix(const Vec3& rotation);
Mat4 Get3DScaleMatrix(const Vec3& scale);
