#pragma once
class Window;

class IInputHandler{
public:
    virtual void handleInput(Window& window, int key, int scancode, int action, int mods) = 0;
};
