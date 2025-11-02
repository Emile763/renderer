#pragma once
#include <string>
#include <GL/glew.h>
#include "Vector.h"
#include "Matrix.h"
#include "ShaderUtils.h"
class Shader {
private:
    static std::string getFileContent(const std::string& path);

    GLuint m_program_id;

    static Shader current_shader;

    static Shader* default_3D_shader;

public:
    Shader();
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    void load(const std::string& vertex_shader, const std::string& fragment_shader);
    void loadFromFiles(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    ~Shader();
    void use() const;

    static void setInt(ShaderVarLocations location, const int& value);
    static void setFloat(ShaderVarLocations location, const float& value);
    static void setVec2(ShaderVarLocations location, const Vec2& value);
    static void setVec3(ShaderVarLocations location, const Vec3& value);
    static void setVec4(ShaderVarLocations location, const Vec4& value);
    static void setMat2(ShaderVarLocations location, const Mat2& value);
    static void setMat3(ShaderVarLocations location, const Mat3& value);
    static void setMat4(ShaderVarLocations location, const Mat4& value);


    static const Shader& getDefault3DShader();

};

Shader loadShader(const std::string& vertex_shader, const std::string& fragment_shader);
