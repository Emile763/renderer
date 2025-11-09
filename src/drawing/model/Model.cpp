#include "Model.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ShaderUtils.h"

Model::Model() : m_VAO(0), m_vertex_VBO(0), m_normal_VBO(0), m_texture_coord_VBO(0)
{
    glCreateVertexArrays(1, &m_VAO);
}


Model::Model(const std::string& obj_path) : Model()
{
    std::ifstream obj_file(obj_path);
    std::vector<std::string> vertice_strings;
    std::vector<std::string> normal_strings;
    std::vector<std::string> texture_coord_strings;

    std::vector<std::string> face_strings;

    std::string line;
    while (std::getline(obj_file, line)) {
        if (line[0] == 'v') {
            switch (line[1])
            {
            case ' ':
                vertice_strings.push_back(line.substr(2));
                break;
            case 't':
                texture_coord_strings.push_back(line.substr(3));
                break;
            case 'n':
                normal_strings.push_back(line.substr(3));
                break;
            default:
                break;
            }
        }
        else if (line[0] == 'f') {
            face_strings.push_back(line.substr(2));
        }
    }

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texture_coords;


    vertices.reserve(face_strings.size() * 3 * 3);
    if (!texture_coord_strings.empty()) {
        texture_coords.reserve(face_strings.size() * 3 * 2);
    }
    if (!normal_strings.empty()) {
        normals.reserve(face_strings.size() * 3 * 3);
    }

    for (auto& face : face_strings) {
        std::replace(face.begin(), face.end(), '/', ' ');
        std::istringstream face_stream(face);

        for (int i = 0; i < 3; i++)
        {
            int vertice_index;
            face_stream >> vertice_index;
            std::istringstream vertex_stream(vertice_strings[vertice_index - 1]);

            float vertice_coord;
            while (vertex_stream >> vertice_coord)
            {
                vertices.push_back(vertice_coord);
            }

            if (!texture_coord_strings.empty()) {
                int texture_coord_index;
                face_stream >> texture_coord_index;
                std::istringstream texture_coord_stream(texture_coord_strings[texture_coord_index - 1]);

                float texture_coord;
                while (texture_coord_stream >> texture_coord)
                {
                    texture_coords.push_back(texture_coord);
                }
            }
            if (!normal_strings.empty()) {
                int normal_index;
                face_stream >> normal_index;
                std::istringstream normal_stream(normal_strings[normal_index - 1]);

                float normal_coord;
                while (normal_stream >> normal_coord)
                {
                    normals.push_back(normal_coord);
                }
            }
        }
    }

    setVertices(vertices);

    if (!normals.empty())
    {
        setNormals(normals);
    }
    if (!texture_coords.empty())
    {
        setTextureCoords(texture_coords);
    }

}

Model::~Model()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_vertex_VBO);
    glDeleteBuffers(1, &m_normal_VBO);
    glDeleteBuffers(1, &m_texture_coord_VBO);
}

void Model::setVertices(const std::vector<float>& vertices, const float& dimension) {
    if (m_vertex_VBO == 0) {
        glCreateBuffers(1, &m_vertex_VBO);
    }
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)ShaderVarLocations::POSITION, dimension, GL_FLOAT, GL_FALSE, dimension * sizeof(float), (void*)(0));
    glEnableVertexAttribArray((GLuint)ShaderVarLocations::POSITION);
    glBindVertexArray(0);

    m_vertices_number = vertices.size() / dimension;

}
void Model::setNormals(const std::vector<float>& normals, const float& dimension) {
    if (m_normal_VBO == 0) {
        glCreateBuffers(1, &m_normal_VBO);
    }
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_normal_VBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)ShaderVarLocations::NORMAL, dimension, GL_FLOAT, GL_FALSE, dimension * sizeof(float), (void*)(0));
    glEnableVertexAttribArray((GLuint)ShaderVarLocations::NORMAL);
    glBindVertexArray(0);

}
void Model::setTextureCoords(const std::vector<float>& texture_coords) {
    if (m_texture_coord_VBO == 0) {
        glCreateBuffers(1, &m_texture_coord_VBO);
    }
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_texture_coord_VBO);
    glBufferData(GL_ARRAY_BUFFER, texture_coords.size() * sizeof(float), texture_coords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)ShaderVarLocations::TEXTURE_COORD, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray((GLuint)ShaderVarLocations::TEXTURE_COORD);
    glBindVertexArray(0);
}

void Model::draw() const
{
    initDrawing();
    endDrawing();
}

void Model::initDrawing() const
{
    glBindVertexArray(m_VAO);
}

void Model::endDrawing() const
{
    glDrawArrays(GL_TRIANGLES, 0, m_vertices_number);
}


