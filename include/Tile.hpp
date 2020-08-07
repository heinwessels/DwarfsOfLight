#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"
#include "CollisionBoxComponent.hpp"

class Tile : public Entity{
public:
    typedef int Type;
    static constexpr Type TypeEmpty = 0;
    static constexpr Type TypeAir = 1;
    static constexpr Type TypeWall = 2;

private:

    float width = 32;
    float height = 32;
    std::string m_texture_path = "textures/tile_eg.png";
    Type m_type;

public:
    Tile() : Entity(Vec2(0.0, 0.0)), m_type(TypeEmpty) { }  // For empty world tiles
    Tile(Type type, float x, float y) : Entity(Vec2(x, y)), m_type(type) {
        if(m_type == TypeWall){
            this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
            this->add_component(std::make_unique<CollisionBox>(width, height, false, true));
        }
    }
};