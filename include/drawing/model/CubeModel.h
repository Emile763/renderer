#pragma once
#include "Model.h"

class CubeModel : public Model {
private:
    static CubeModel* m_cube;
    CubeModel();

public:
    CubeModel(CubeModel&) = delete;
    void operator=(const CubeModel&) = delete;

    static const CubeModel& getInstance();
    static void deleteInstance();
};