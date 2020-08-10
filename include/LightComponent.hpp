#pragma once

#include "Component.hpp"
#include "MColour.hpp"


class LightComponent : public Component{
public:
    MColour base_colour;
    MColour current_colour;
    MColour colour_variation;
    MColour current_gradient;

    float period;
    float time_to_gradient_change = 0;
    float range;  // How far does this light shine?

    LightComponent(MColour base_colour, MColour colour_variation, float period, float range)
        : Component(LightComponentID),
        base_colour(base_colour),
        current_colour(base_colour),

        colour_variation(colour_variation),

        period(period),
        time_to_gradient_change (period),
        current_gradient(MColour(0)),

        range(range)
        { }

};

