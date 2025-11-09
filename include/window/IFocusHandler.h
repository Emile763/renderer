#pragma once
class Window;

class IFocusHandler{
public:
    virtual void handleFocus(Window& window, bool focused) = 0;
};
