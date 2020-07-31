#pragma once

#include <memory>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"

class Dwarf : public Entity{

public:
    Dwarf(SDL_Texture* texture);
};