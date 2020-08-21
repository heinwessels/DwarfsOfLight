#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Component.hpp"
#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "CollisionBoxComponent.hpp"
#include "MoveComponent.hpp"

class Firefly : public Entity{

private:
    double width = 0.5;
    double height = 0.5;
    std::string m_texture_path = "textures/dwarf.png";

public:
    Firefly(double x, double y) : Entity("Firefly") {
        this->add_component<TransformComponent>(Vec2(x, y));
        this->add_component<MoveComponent>(MoveComponent::TypeSporadic);
        this->add_component<Renderable>(m_texture_path, width, height);
        this->add_component<CollisionBox>(width, height);
    }
};