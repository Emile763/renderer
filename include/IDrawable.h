#pragma once
#include <GL/glew.h>

class IDrawable{
    
public:
    virtual GLuint getVAO() const = 0;
    virtual unsigned int getVerticesNumber() const = 0;
};