#include "Shader.h"
#include <iostream>
#include <fstream>
#include <filesystem>

const std::string default_3D_shader_code_vertex{
    "#version 460\n"
    "layout(location = 0) in vec3 a_position;\n"
    "layout(location = 1) in vec3 a_normal;\n"

    "layout(location = 4) uniform mat4 projection;\n"
    "layout(location = 5) uniform mat4 translation;\n"
    "layout(location = 6) uniform mat4 rotation;\n"
    "layout(location = 7) uniform mat4 scale;\n"
    "layout(location = 8) uniform mat4 view;\n"

    "out vec3 w_normal;\n"

    "void main(){\n"
    // TODO: move to CPU
    "    mat4 model = translation * rotation * scale;\n"
    "    mat3 normale_mat = mat3(transpose(inverse(model)));\n"

    "    w_normal    = normale_mat * a_normal;\n"
    "    gl_Position =  projection * view * model * vec4(a_position, 1.f);\n"
    "}" };

const std::string default_3D_shader_code_fragment{
"#version 460\n"
"layout(location = 0) out vec4 color;\n"

"layout(location = 9) uniform vec3 camera_pos;\n"

"in vec3 w_normal;\n"

"void main(){\n"
"    color = vec4((w_normal + vec3(1.f,1.f,1.f)) / 2.f, 1.f);\n"
"}" };


Shader* Shader::default_3D_shader = nullptr;


std::string Shader::getFileContent(const std::string& path) {
    std::ifstream file(path);
    auto size = std::filesystem::file_size(path);
    std::string result(size + 1, '\0');
    file.read(result.data(), size);
    file.close();
    return result;
}

bool checkShaderCompilation(GLuint shader_id) {
    GLint isCompiled;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int info_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);

        std::string errorLog(info_length, '\0');
        glGetShaderInfoLog(shader_id, info_length, &info_length, errorLog.data());
        std::cerr << errorLog;
        return false;
    }
    return true;
}

bool checkProgramLink(GLuint program_id) {

    GLint isLinked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint info_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);

        // The maxLength includes the NULL character
        std::string errorLog(info_length, '\0');
        glGetProgramInfoLog(program_id, info_length, &info_length, errorLog.data());

        // The program is useless now. So delete it.
        glDeleteProgram(program_id);
        program_id = 0;

        return false;
    }
    return true;
}

Shader::Shader() : m_program_id(0) {}

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {

    this->loadFromFiles(vertex_shader_path, fragment_shader_path);
}


void Shader::load(const std::string& vertex_shader, const std::string& fragment_shader) {
    // Get an opengl shader id for vertex and fragment
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Set the source code for each shader
    const char* c_str_vertex = vertex_shader.c_str();
    glShaderSource(vertex_shader_id, 1, &c_str_vertex, NULL);

    const char* c_str_fragment = fragment_shader.c_str();
    glShaderSource(fragment_shader_id, 1, &c_str_fragment, NULL);

    // Compile the shaders
    glCompileShader(vertex_shader_id);
    glCompileShader(fragment_shader_id);

    if (!checkShaderCompilation(vertex_shader_id)) {
        std::cerr << "Error while compiling vertex shader: " << vertex_shader;
    }

    if (!checkShaderCompilation(fragment_shader_id)) {
        std::cerr << "Error while compiling fragment shader: " << fragment_shader;
    }


    // Create the program, attach the shaders and link them
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader_id);
    glAttachShader(m_program_id, fragment_shader_id);
    glLinkProgram(m_program_id);

    if (!checkProgramLink(m_program_id)) {
        std::cerr << "Error while linking the shaders: \n";
        std::cerr << "   Vertex   -> " << vertex_shader << "\n";
        std::cerr << "   Fragment -> " << fragment_shader << "\n";
    }


    // delete shaders, not needed anymore
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

}

void Shader::loadFromFiles(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
    // Get the vertex and fragment shader code
    std::string vertex_shader_string = getFileContent(vertex_shader_path);
    std::string fragment_shader_string = getFileContent(fragment_shader_path);
    this->load(vertex_shader_string, fragment_shader_string);
}


Shader::~Shader() {
    if (m_program_id != 0)
        glDeleteProgram(m_program_id);
}

void Shader::use() const {
    glUseProgram(m_program_id);
}


void Shader::setInt(ShaderVarLocations location, const int& value) {
    glUniform1i((int)location, value);
}
void Shader::setFloat(ShaderVarLocations location, const float& value) {
    glUniform1f((int)location, value);
}
void Shader::setVec2(ShaderVarLocations location, const Vec2& value) {
    glUniform2f((int)location, value[0], value[1]);
}
void Shader::setVec3(ShaderVarLocations location, const Vec3& value) {
    glUniform3f((int)location, value[0], value[1], value[2]);
}
void Shader::setVec4(ShaderVarLocations location, const Vec4& value) {
    glUniform4f((int)location, value[0], value[1], value[2], value[3]);
}
void Shader::setMat2(ShaderVarLocations location, const Mat2& value) {
    glUniformMatrix2fv((int)location, 1, GL_TRUE, value.getData());
}
void Shader::setMat3(ShaderVarLocations location, const Mat3& value) {
    glUniformMatrix3fv((int)location, 1, GL_TRUE, value.getData());
}
void Shader::setMat4(ShaderVarLocations location, const Mat4& value) {
    glUniformMatrix4fv((int)location, 1, GL_TRUE, value.getData());
}

Shader loadShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    Shader shader;
    shader.load(vertex_shader, fragment_shader);
    return shader;
}

const Shader& Shader::getDefault3DShader()
{

    if (default_3D_shader == nullptr)
    {
        default_3D_shader = new Shader();
        default_3D_shader->load(default_3D_shader_code_vertex, default_3D_shader_code_fragment);
    }

    return *default_3D_shader;
}
