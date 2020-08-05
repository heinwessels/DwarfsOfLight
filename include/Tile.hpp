#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"
#include "CollisionBoxComponent.hpp"

class Tile : public Entity{

private:
    float width = 32;
    float height = 32;
    std::string m_texture_path = "textures/tile_eg.png";

public:
    Tile(float x, float y) : Entity(Vec2(x, y)) {
        this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
    }
};