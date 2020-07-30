#pragma once

#include "Component.h"

class Renderable : public Component {

public:

    // Don't know yet how I will inject data
    virtual void init() override;

};