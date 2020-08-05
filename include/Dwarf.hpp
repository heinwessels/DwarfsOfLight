#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"

class Dwarf : public Entity{

private:
    float width = 32;
    float height = 32;
    std::string m_texture_path = "textures/dwarf.png";

public:
    Dwarf(float x, float y) : Entity(Vec2 (x, y)) {
        this->add_component(std::make_unique<MoveComponent>(Vec2(0.0f, 0.0f)));
        this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
        this->add_component(std::make_unique<ControllerComponent>(10));
        this->add_component(std::make_unique<CollisionBox>(width, height));
    }
};