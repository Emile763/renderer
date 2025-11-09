#pragma once
#include "Vector.h"
#include <GL/glew.h>
#include <string>
#include <vector>
class Texture
{
private:
    GLuint m_texture_id;
    float m_width;
    float m_height;
    void setTexture(const unsigned char* data, const unsigned int &width, const unsigned int &height, const unsigned int &channels_number);
public:
    Texture();
    Texture(const std::string& image_path);
    Texture(const std::vector<unsigned char> image_bmp_data, const unsigned int& width, const unsigned int& height, const unsigned int& channels_number);
    ~Texture();

    void setTexture(const std::vector<unsigned char> image_bmp_data, const unsigned int &width, const unsigned int &height, const unsigned int &channels_number);

    GLuint getTextureId() const;

    const float& getWidth() const;
    const float& getHeight() const;

    const Vec2 getSize() const;
};
