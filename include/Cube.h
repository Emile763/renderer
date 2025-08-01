#pragma once
#include "Drawable.h"
#include <GL/glew.h>

class Cube : public Drawable {
private:
    GLuint m_VAO;
    GLuint m_vertex_VBO;
public:
    Cube();
    ~Cube();

    GLuint getVAO() const override;
    unsigned int getVerticesNumber() const override;
};