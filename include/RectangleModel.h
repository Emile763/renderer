#pragma once
#include "Model.h"

class RectangleModel : public Model {
private:
    static RectangleModel* m_rectangle;
    RectangleModel();

public:
    RectangleModel(RectangleModel&) = delete;
    void operator=(const RectangleModel&) = delete;

    static const RectangleModel& getInstance();
    static void deleteInstance();
};