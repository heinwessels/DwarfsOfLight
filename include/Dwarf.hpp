#pragma once

#include <memory>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"

class Dwarf : public Entity{

private:
    float width = 32;
    float height = 32;

public:
    Dwarf(SDL_Texture* texture, float x, float y);
};