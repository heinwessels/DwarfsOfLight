#pragma once

#include "Component.hpp"
#include "MColour.hpp"


class LightComponent : public Component{
    MColour m_base_colour;
    MColour m_colour_weight;
    MColour m_frequency;
public:
    LightComponent() : Component(LightComponentID) { }
};

