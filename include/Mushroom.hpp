#pragma once

#include <memory>
#include "Entity.hpp"

#include "Component.hpp"
#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "LightComponent.hpp"
#include "LifeComponent.hpp"
#include "TeamComponent.hpp"

class Mushroom : public Entity{

private:
    double width = 0.6;
    double height = 0.5;

public:
    Mushroom(double x, double y) : Entity("Mushroom") {
        this->add_component<TransformComponent>(Vec2(x, y));
        this->add_component<Renderable>("textures/mushroom.png", width, height);
        this->add_component<LightComponent>(MColour(100, 150, 250), MColour(10, 10, 10), 1, 3);
        this->add_component<TeamComponent>(TeamPlant, 1);
        this->add_component<FungiLifeComponent>(30, 20, 10);
    }
};