#include "DrawingQueue.h"
#include <algorithm>

DrawingQueue::DrawingQueue() : m_shader(Shader::getDefault3DShader()) {}

DrawingQueue::DrawingQueue(const Shader& shader) : m_shader(shader) {}

void DrawingQueue::add(const IDrawable& drawable, const IShaderParameter& parameter)
{
    m_to_render[&drawable].push_back(&parameter);
}

void DrawingQueue::remove(const IDrawable& drawable, const IShaderParameter& parameter)
{
    // Expensive when using vector
    auto pair = m_to_render.find(&drawable);
    if(pair != m_to_render.end()){
        auto element = std::find(pair->second.cbegin(), pair->second.cend(), &parameter);
        if (element != pair->second.cend())
        {
            pair->second.erase(element);
            if(pair->second.empty())
                m_to_render.erase(&drawable);
        }
    }
}

void DrawingQueue::addInitParameter(const IShaderParameter& parameter)
{
    m_shader_init_parameters.push_back(&parameter);
}

void DrawingQueue::draw() const
{
    initDrawing();
    endDrawing();
}

void DrawingQueue::initDrawing() const{
    m_shader.use();
    for (const IShaderParameter* parameter : m_shader_init_parameters)
    {
        parameter->setShaderParameters();
    }
}

void DrawingQueue::endDrawing() const {
    for (auto itr = m_to_render.cbegin(); itr != m_to_render.cend(); itr++)
    {
        itr->first->initDrawing();
        for (const IShaderParameter* parameter : itr->second)
        {
            if (parameter != nullptr)
                parameter->setShaderParameters();
            itr->first->endDrawing();
        }
    }
}

void DrawingQueue::clear() {
    clearQueue();
    clearInitParameter();
}
void DrawingQueue::clearQueue() {
    m_to_render.clear();
}
void DrawingQueue::clearInitParameter() {
    m_shader_init_parameters.clear();
}
