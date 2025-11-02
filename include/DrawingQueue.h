#pragma once
#include "IDrawable.h"
#include "IShaderParameter.h"
#include "Shader.h"
#include "EmptyShaderParameter.h"
#include <unordered_map>
#include <vector>

class DrawingQueue : IDrawable{
private:
    const Shader& m_shader;
    std::vector<const IShaderParameter*> m_shader_init_parameters;
    std::unordered_map<const IDrawable*, std::vector<const IShaderParameter*>> m_to_render;
public:
    DrawingQueue();
    DrawingQueue(const Shader& shader);

    void add(const IDrawable& drawable, const IShaderParameter& parameter = EmptyShaderParameter::getIntance());
    void remove(const IDrawable& drawable, const IShaderParameter& parameter = EmptyShaderParameter::getIntance());
    void addInitParameter(const IShaderParameter& parameter);

    void draw() const override;

    void initDrawing() const override;
    void endDrawing() const override;

    void clear();
    void clearQueue();
    void clearInitParameter();

};
