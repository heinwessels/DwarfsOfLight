#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"
#include "LightComponent.hpp"

class Dwarf : public Entity{

private:
    double width = 1.5;
    double height = 1.5;
    std::string m_texture_path = "textures/dwarf2.jpg";

public:
    Dwarf(double x, double y) : Entity(Vec2 (x, y)) {
        this->add_component(std::make_unique<MoveComponent>(Vec2(0.0f, 0.0f)));
        this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
        this->add_component(std::make_unique<ControllerComponent>(5));
        this->add_component(std::make_unique<CollisionBox>(width, height));
        this->add_component(std::make_unique<LightComponent>(
            // MColour(230, 150, 0), MColour(20, 50, 0), 1, 10
            MColour(230, 180, 180), MColour(20, 20, 0), 1, 20
        ));
    }
};