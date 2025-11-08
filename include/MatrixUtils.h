#pragma once
#include "Vector.h"
#include "Matrix.h"


Mat4 Get3DXRotationMatrix(const float& angle);
Mat4 Get3DYRotationMatrix(const float& angle);
Mat4 Get3DZRotationMatrix(const float& angle);

Mat4 Get3DTranslationMatrix(const Vec3& position);
Mat4 GetEulerRotationMatrix(const Vec3& rotation);
Mat4 Get3DRotationMatrix(const Vec3& rotation);
Mat4 Get3DScaleMatrix(const Vec3& scale);


Mat3 Get2DRotationMatrix(const float& rotation);
