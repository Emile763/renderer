#pragma once
#include "Model.h"

class Cube : public Model {
private:
    static Cube* m_cube;
    Cube();

public:
    Cube(Cube&) = delete;
    void operator=(const Cube&) = delete;

    static const Cube& getInstance();
    static void deleteInstance();
};