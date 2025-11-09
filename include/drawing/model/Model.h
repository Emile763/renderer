#pragma once
#include <string>
#include <vector>
#include "IDrawable.h"

class Model : public IDrawable
{
private:
    unsigned int m_vertices_number;

    GLuint m_VAO;
    GLuint m_vertex_VBO;
    GLuint m_normal_VBO;
    GLuint m_texture_coord_VBO;

public:
    Model();
    Model(const std::string& obj_path);
    ~Model();

    void setVertices(const std::vector<float>& vertices, const float& dimension = 3);
    void setNormals(const std::vector<float>& normals, const float& dimension = 3);
    void setTextureCoords(const std::vector<float>& texture_coord);

    void draw() const override;

    void initDrawing() const override;
    void endDrawing() const override;

    // void saveAsBinobj(const std::string& path, const std::string& name);
};
