#pragma once

#include <vector>
#include <memory>
#include <stdio.h>

#include "Component.hpp"

#include "Renderable.hpp"
#include "MoveComponent.hpp"

class Renderable;

class GameObject{

public:

    // Here follows all possible components. They will only be populated if used
    std::unique_ptr<Renderable> m_renderable = nullptr;
    std::unique_ptr<MoveComponent> m_moveComponent = nullptr;

    GameObject() { }

};