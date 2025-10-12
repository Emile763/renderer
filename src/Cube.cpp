#include "Cube.h"
#include "ShaderUtils.h"
constexpr float cube_vertices[] = {
    
    // S face
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
    -1.0,  1.0, -1.0,
    
    -1.0,  1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,

    // N face
    -1.0, -1.0, 1.0,
     1.0, -1.0, 1.0,
    -1.0,  1.0, 1.0,
    
    -1.0,  1.0, 1.0,
     1.0, -1.0, 1.0,
     1.0,  1.0, 1.0,

    // E face
    1.0, -1.0, -1.0, 
    1.0,  1.0, -1.0, 
    1.0, -1.0,  1.0, 
    
    1.0, -1.0,  1.0, 
    1.0,  1.0, -1.0, 
    1.0,  1.0,  1.0,

    // W face
    -1.0, -1.0, -1.0, 
    -1.0,  1.0, -1.0, 
    -1.0, -1.0,  1.0, 
    
    -1.0, -1.0,  1.0, 
    -1.0,  1.0, -1.0, 
    -1.0,  1.0,  1.0, 

    // Top face
    -1.0, 1.0, -1.0, 
     1.0, 1.0, -1.0, 
    -1.0, 1.0,  1.0, 
    
    -1.0, 1.0,  1.0, 
     1.0, 1.0, -1.0, 
     1.0, 1.0,  1.0,

    // Bottom face
    -1.0, -1.0, -1.0, 
     1.0, -1.0, -1.0, 
    -1.0, -1.0,  1.0, 
    
    -1.0, -1.0,  1.0, 
     1.0, -1.0, -1.0, 
     1.0, -1.0,  1.0, 

};

constexpr unsigned int number_of_vertices = sizeof(cube_vertices) / sizeof(float) / 3;

Cube::Cube()
{
    glCreateVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)ShaderVarLocations::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray((GLuint)ShaderVarLocations::POSITION);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_vertex_VBO);
}

GLuint Cube::getVAO() const
{
    return m_VAO;
}

unsigned int Cube::getVerticesNumber() const
{
    return number_of_vertices;
}
