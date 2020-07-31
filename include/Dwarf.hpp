#pragma once

#include <memory>

#include "GameObject.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"

class Dwarf : public GameObject{

public:
    Dwarf(float x, float y, SDL_Texture* texture);
};