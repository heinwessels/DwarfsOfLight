#pragma once

#include "Component.hpp"
#include "MColour.hpp"


class LightComponent : public Component{
public:
    MColour base_colour;
    MColour current_colour;
    MColour colour_variation;
    MColour current_gradient;
    MColour frequency;

    float range;  // How far does this light shine?

    LightComponent(MColour base_colour, MColour colour_variation, MColour frequency, float range)
        : Component(LightComponentID),
        base_colour(base_colour), current_colour(base_colour),
        colour_variation(colour_variation), frequency(frequency),
        range(range), current_gradient(MColour(0)) { }
};

