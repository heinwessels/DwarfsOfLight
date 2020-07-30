#pragma once

#include "SystemBase.h"

class System : public SystemBase{

public:
    virtual ~System() = default;
    virtual void init() = 0;

    // This update must loop through "entities" and
    // look for ones that has all components this system requries.
    virtual void update(float dT) = 0;
};