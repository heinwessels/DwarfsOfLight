#pragma once

#include "Component.hpp"
#include "MColour.hpp"


class LightComponent : public Component{
public:
    MColour base_colour;
    MColour current_colour;
    MColour colour_weight;
    MColour current_gradient;
    MColour frequency;

    float max_dist = 5;

    LightComponent(MColour base_colour, MColour colour_weight, MColour frequency)
        : Component(LightComponentID),
        base_colour(base_colour), current_colour(base_colour),
        colour_weight(colour_weight), frequency(frequency), current_gradient(MColour(0)) { }
};

