#include "RectangleModel.h"
#include <vector>

constexpr float rectangle_vertices[] = {
    -1.0, -1.0,
    1.0, -1.0,
    -1.0,  1.0,

    -1.0,  1.0,
    1.0, -1.0,
     1.0,  1.0,
};

constexpr float rectangle_texture_coords[] = {
    0.0, 0.0,
    1.0, 0.0,
    0.0, 1.0,

    0.0, 1.0,
    1.0, 0.0,
    1.0, 1.0,
};

RectangleModel* RectangleModel::m_rectangle = nullptr;

RectangleModel::RectangleModel() : Model()
{
    this->setVertices(std::vector<float>(rectangle_vertices, rectangle_vertices + sizeof(rectangle_vertices) / sizeof(float)), 2);
    this->setTextureCoords(std::vector<float>(rectangle_texture_coords, rectangle_texture_coords + sizeof(rectangle_texture_coords) / sizeof(float)));
}

const RectangleModel& RectangleModel::getInstance()
{
    if (m_rectangle == nullptr)
        m_rectangle = new RectangleModel;
    return *m_rectangle;
}

void RectangleModel::deleteInstance()
{
    if (m_rectangle != nullptr)
    {
        delete m_rectangle;
        m_rectangle = nullptr;
    }
}

