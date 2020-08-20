#pragma once

#include "Component.hpp"
#include "MColour.hpp"

class LightComponent : public Component{
public:
    static constexpr ComponentID ID = LightComponentID;

    MColour base_colour;
    MColour current_colour;

    MColour colour_variation;
    double period;

    MColour current_gradient;
    double time_to_gradient_change = 0;

    double range;  // How far does this light shine?

    LightComponent(MColour base_colour, MColour colour_variation, double period, double range)
        : Component(ID),
        base_colour(base_colour),
        current_colour(base_colour),

        colour_variation(colour_variation),

        period(period),
        current_gradient(MColour(0)),

        range(range)
        { }

};

