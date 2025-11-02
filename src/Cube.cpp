#include "Cube.h"
#include <vector>

constexpr float cube_vertices[] = {
    
    // S face
    -1.0, -1.0, -1.0,
    -1.0,  1.0, -1.0,
     1.0, -1.0, -1.0,
    
    -1.0,  1.0, -1.0,
    1.0,  1.0, -1.0,
    1.0, -1.0, -1.0,

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
    -1.0, -1.0,  1.0, 
    -1.0,  1.0, -1.0, 
    
    -1.0, -1.0,  1.0, 
    -1.0,  1.0,  1.0, 
    -1.0,  1.0, -1.0, 

    // Top face
    -1.0, 1.0, -1.0, 
    -1.0, 1.0,  1.0, 
     1.0, 1.0, -1.0, 
    
    -1.0, 1.0,  1.0, 
     1.0, 1.0,  1.0,
     1.0, 1.0, -1.0, 

    // Bottom face
    -1.0, -1.0, -1.0, 
     1.0, -1.0, -1.0, 
    -1.0, -1.0,  1.0, 
    
    -1.0, -1.0,  1.0, 
     1.0, -1.0, -1.0, 
     1.0, -1.0,  1.0, 

};

constexpr float cube_normals[] = {
    
    // S face
    0, 0, -1.0,
    0, 0, -1.0,
    0, 0, -1.0,
    
    0, 0, -1.0,
    0, 0, -1.0,
    0, 0, -1.0,

    // N face
    0, 0, 1.0,
    0, 0, 1.0,
    0, 0, 1.0,
    
    0, 0, 1.0,
    0, 0, 1.0,
    0, 0, 1.0,

    // E face
    1.0, 0, 0, 
    1.0, 0, 0, 
    1.0, 0, 0, 
    
    1.0, 0, 0, 
    1.0, 0, 0, 
    1.0, 0, 0,

    // W face
    -1.0, 0, 0, 
    -1.0, 0, 0, 
    -1.0, 0, 0, 

    -1.0, 0, 0, 
    -1.0, 0, 0, 
    -1.0, 0, 0, 

    // Top face
    0, 1.0, 0, 
    0, 1.0, 0, 
    0, 1.0, 0, 
    
    0, 1.0, 0, 
    0, 1.0, 0, 
    0, 1.0, 0,

    // Bottom face
    0, -1.0, 0, 
    0, -1.0, 0, 
    0, -1.0, 0, 
    
    0, -1.0, 0, 
    0, -1.0, 0, 
    0, -1.0, 0, 

};


Cube* Cube::m_cube = nullptr;



Cube::Cube() : Model()
{
    this->setVertices(std::vector<float>(cube_vertices, cube_vertices + sizeof(cube_vertices) / sizeof(float)));
    this->setNormals(std::vector<float>(cube_normals, cube_normals + sizeof(cube_normals) / sizeof(float)));
}

const Cube& Cube::getInstance()
{
    if(m_cube == nullptr)
        m_cube = new Cube;
    return *m_cube;
}

void Cube::deleteInstance()
{
    if(m_cube != nullptr)
    {
        delete m_cube;
        m_cube = nullptr;
    }
}

