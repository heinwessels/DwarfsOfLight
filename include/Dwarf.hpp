#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Component.hpp"
#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "LightComponent.hpp"
#include "ControllerComponent.hpp"
#include "MoveComponent.hpp"

class Dwarf : public Entity{

private:
    double width = 1.5;
    double height = 1.5;
    std::string m_texture_path = "textures/dwarf2.jpg";

public:
    Dwarf(double x, double y) : Entity("Dwarf") {
        this->add_component<TransformComponent>(Vec2(x, y));
        this->add_component<ControllerComponent>();
        this->add_component<MoveComponent>(MoveComponent::TypeStraight, 5);
        this->add_component<Renderable>(m_texture_path, width, height);
        this->add_component<CollisionBox>(width, height);
        this->add_component<LightComponent>(MColour(230, 180, 180), MColour(20, 20, 0), 1, 20);
    }
};