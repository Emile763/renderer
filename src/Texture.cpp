#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

void Texture::setTexture(const unsigned char* data, const unsigned int& width, const unsigned int& height, const unsigned int& channels_number)
{
    m_width = width;
    m_height = height;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    if(channels_number == 4){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }else if(channels_number == 3){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::Texture()
{
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& image_path) : Texture()
{
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char* data = stbi_load(image_path.c_str(), &width, &height, &channels, 0);
    assert(data);
    setTexture(data, (unsigned int)width, (unsigned int)height, (unsigned int)channels);
    
    stbi_image_free(data);
}

Texture::Texture(const std::vector<unsigned char> image_bmp_data, const unsigned int& width, const unsigned int& height, const unsigned int& channels_number) : Texture()
{
    setTexture(image_bmp_data, width, height, channels_number);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture_id);
}

void Texture::setTexture(const std::vector<unsigned char> image_bmp_data, const unsigned int& width, const unsigned int& height, const unsigned int& channels_number)
{
    assert(width + height == image_bmp_data.size());
    setTexture(image_bmp_data.data(), width, height, channels_number);
}

GLuint Texture::getTextureId() const
{
    return m_texture_id;
}

const float& Texture::getWidth() const
{
    return m_width;
}

const float& Texture::getHeight() const
{
    return m_height;
}

const Vec2 Texture::getSize() const
{
    return Vec2{m_width, m_height};
}
