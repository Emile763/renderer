#include "Model.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ShaderUtils.h"
GLuint Model::getVAO() const
{
    return m_VAO;
}

unsigned int Model::getVerticesNumber() const
{
    return m_vertices.size() / 3;
}

Model::Model(const std::string& obj_path)
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

    for (auto& face : face_strings) {
        std::replace(face.begin(), face.end(), '/', ' ');
        std::istringstream face_stream(face);

        for (int i = 0; i < 3; i++)
        {
            int vertice_index;
            face_stream >> vertice_index;
            std::istringstream vertex_stream(vertice_strings[vertice_index-1]);

            float vertice_coord;
            while (vertex_stream >> vertice_coord)
            {
                m_vertices.push_back(vertice_coord);
            }

            if (!texture_coord_strings.empty()) {
                int texture_coord_index;
                face_stream >> texture_coord_index;
                std::istringstream texture_coord_stream(texture_coord_strings[texture_coord_index-1]);

                float texture_coord;
                while (texture_coord_stream >> texture_coord)
                {
                    m_texture_coords.push_back(texture_coord);
                }
            }
            if (!normal_strings.empty()) {
                int normal_index;
                face_stream >> normal_index;
                std::istringstream normal_stream(normal_strings[normal_index-1]);

                float normal_coord;
                while (normal_stream >> normal_coord)
                {
                    m_normals.push_back(normal_coord);
                }
            }
        }
    }
    m_vertices.shrink_to_fit();
    m_normals.shrink_to_fit();
    m_texture_coords.shrink_to_fit();


    glCreateVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glCreateBuffers(1, &m_vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)ShaderVarLocations::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray((GLuint)ShaderVarLocations::POSITION);
    if (!m_normals.empty())
    {
        glCreateBuffers(1, &m_normal_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_normal_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(float), m_normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)ShaderVarLocations::NORMAL, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray((GLuint)ShaderVarLocations::NORMAL);
    }
    if (!m_texture_coords.empty())
    {
        glCreateBuffers(1, &m_texture_coord_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_texture_coord_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_texture_coords.size() * sizeof(float), m_texture_coords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)ShaderVarLocations::TEXTURE_COORD, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray((GLuint)ShaderVarLocations::TEXTURE_COORD);
    }
    
    glBindVertexArray(0);
}

Model::~Model()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_vertex_VBO);
    glDeleteBuffers(1, &m_normal_VBO);
    glDeleteBuffers(1, &m_texture_coord_VBO);
}

void Model::saveAsBinobj(const std::string& path, const std::string& name)
{

}
