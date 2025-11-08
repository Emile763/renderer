#include "MatrixUtils.h"
#include <cmath>
Mat4 Get3DTranslationMatrix(const Vec3& position) {
    return Mat4({
        1.f, 0.f, 0.f, position[0],
        0.f, 1.f, 0.f, position[1],
        0.f, 0.f, 1.f, position[2],
        0.f, 0.f, 0.f, 1.f
        });
}

Mat4 Get3DXRotationMatrix(const float& angle) {
    float cos_angle = std::cosf(angle);
    float sin_angle = std::sinf(angle);
    return {
        1.f, 0.f,        0.f,       0.f,
        0.f, cos_angle, -sin_angle, 0.f,
        0.f, sin_angle,  cos_angle, 0.f,
        0.f, 0.f,        0.f,       1.f,
    };
}

Mat4 Get3DYRotationMatrix(const float& angle) {
    float cos_angle = std::cosf(angle);
    float sin_angle = std::sinf(angle);
    return {
        cos_angle,  0.f,  sin_angle, 0.f,
        0.f,        1.f,  0.f,       0.f,
        -sin_angle, 0.f,  cos_angle, 0.f,
        0.f,        0.f,  0.f,       1.f,
    };
}

Mat4 Get3DZRotationMatrix(const float& angle) {
    float cos_angle = std::cosf(angle);
    float sin_angle = std::sinf(angle);
    return {
        cos_angle,  -sin_angle, 0.f, 0.f,
        sin_angle, cos_angle,   0.f, 0.f,
        0.f,        0.f,        1.f, 0.f,
        0.f,        0.f,        0.f, 1.f,
    };
}

Mat4 Get3DRotationMatrix(const Vec3& rotation) {

    Mat4 rotation_X = Get3DXRotationMatrix(rotation[0]);
    Mat4 rotation_Y = Get3DYRotationMatrix(rotation[1]);
    Mat4 rotation_Z = Get3DZRotationMatrix(rotation[2]);

    return rotation_X * rotation_Y * rotation_Z;
}

Mat4 GetEulerRotationMatrix(const Vec3& rotation) {
    float psy = rotation[0];
    float theta = rotation[1];
    float phi = rotation[2];

    float cos_psy = std::cosf(psy);
    float sin_psy = std::sinf(psy);

    float cos_theta = std::cosf(theta);
    float sin_theta = std::sinf(theta);

    float cos_phi = std::cosf(phi);
    float sin_phi = std::sinf(phi);

    Mat4 rotationMatrix = {
        cos_psy * cos_phi - sin_psy * cos_theta * sin_phi, -cos_psy * sin_phi - sin_psy * cos_theta * cos_phi,  sin_psy * sin_theta , 0.f,
        sin_psy * cos_phi + cos_psy * cos_theta * sin_phi, -sin_psy * sin_phi + cos_psy * cos_theta * cos_phi, -cos_psy * sin_theta , 0.f,
        sin_theta * sin_phi                              ,  sin_theta * cos_phi                                ,  cos_theta           , 0.f,
        0.f                                              ,  0.f                                                ,  0.f                 , 1.f
    };

    return rotationMatrix;
}

Mat4 Get3DScaleMatrix(const Vec3& scale) {
    return Mat4({
        scale[0], 0.f, 0.f, 0.f,
        0.f, scale[1], 0.f, 0.f,
        0.f, 0.f, scale[2], 0.f,
        0.f, 0.f, 0.f, 1.f,
        });
}

Mat3 Get2DRotationMatrix(const float& rotation)
{
    float cos_angle = std::cosf(rotation);
    float sin_angle = std::sinf(rotation);
    return Mat3{
        cos_angle, -sin_angle, 0.f,
        sin_angle,  cos_angle, 0.f,
        0.f,        0.f,       1.f
    };
}
