#pragma once
#include <string>
#include <vector>
#include "IDrawable.h"

class Model : public IDrawable
{
private:
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_texture_coords;

    GLuint m_VAO;
    GLuint m_vertex_VBO;
    GLuint m_normal_VBO;
    GLuint m_texture_coord_VBO;

public:
    Model(const std::string& obj_path);
    ~Model();
    
    GLuint getVAO() const override;
    unsigned int getVerticesNumber() const override;
    void saveAsBinobj(const std::string& path, const std::string& name);
};
