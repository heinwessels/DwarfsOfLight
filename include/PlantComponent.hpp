#pragma once

#include <vector>
#include "Component.hpp"

class PlantComponent : public Component{
public:
    static constexpr ComponentID ID = PlantComponentID;

    PlantComponent() : Component(ID) { }
};