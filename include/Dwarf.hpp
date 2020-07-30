#pragma once

#include <memory>

#include "GameObject.hpp"
#include "MoveComponent.hpp"

class Dwarf : public GameObject{

public:
    Dwarf(){
        this->add_component(std::make_unique<MoveComponent>());
    }
};