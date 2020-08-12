#pragma once

#include <memory>
#include <string>

#include "RNG.hpp"
#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"
#include "CollisionBoxComponent.hpp"

class Tile : public Entity{
public:
    typedef int Type;
    static constexpr Type TypeEmpty = 0;
    static constexpr Type TypeAir = 1;
    static constexpr Type TypeFloor = 2;
    static constexpr Type TypeWall = 3;

private:

    double width = 1;
    double height = 1;
    Type m_type;

    MColour lighting = MColour(0);

public:
    Tile() : Entity(Vec2(0.0, 0.0)), m_type(TypeEmpty) { }  // For empty world tiles
    Tile(Type type, double x, double y) : Entity(Vec2(x, y)), m_type(type) {
        if(m_type == TypeWall){
            this->add_component(std::make_unique<Renderable>(
                "textures/wall_tile_atlas.jpg", width, height,
                4, 4, random_int_in_range(0, 4), random_int_in_range(0, 3)
            ));
            this->add_component(std::make_unique<CollisionBox>(width, height, false, true));
        }
        else if (m_type == TypeFloor){
            this->add_component(std::make_unique<Renderable>(
                "textures/dungeon_tiles_2.jpg", width, height,
                4, 4, random_int_in_range(0, 4), random_int_in_range(0, 4)
            ));
        }
    }

    Type get_type(){ return m_type; }
};