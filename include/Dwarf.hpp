#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"
#include "LightComponent.hpp"

class Dwarf : public Entity{

private:
    double width = 1;
    double height = 1;
    std::string m_texture_path = "textures/dwarf.png";

public:
    Dwarf(double x, double y) : Entity(Vec2 (x, y)) {
        this->add_component(std::make_unique<MoveComponent>(Vec2(0.0f, 0.0f)));
        this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
        this->add_component(std::make_unique<ControllerComponent>(5));
        this->add_component(std::make_unique<CollisionBox>(width, height));
        this->add_component(std::make_unique<LightComponent>(
            MColour(200, 50, 0), MColour(10, 10, 10), 0.1, 10
        ));
    }
};