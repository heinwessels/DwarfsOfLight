#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"
#include "CollisionBoxComponent.hpp"

class Goblin : public Entity{

private:
    float width = 32;
    float height = 32;
    std::string m_texture_path = "textures/dwarf.png";

public:
    Goblin(float x, float y){
        this->add_component(std::make_unique<MoveComponent>(Vec2(x, y), Vec2(0.0f, 0.0f)));
        this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
        this->add_component(std::make_unique<CollisionBox>(width, height, false, false));
    }
};