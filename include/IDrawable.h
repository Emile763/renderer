#pragma once
#include <GL/glew.h>

class IDrawable {
public:
    virtual ~IDrawable() = default;

    // Init and end drawing
    virtual void draw() const = 0;

    // Can be needed for optimisation
    virtual void initDrawing() const = 0;
    virtual void endDrawing() const = 0;
};