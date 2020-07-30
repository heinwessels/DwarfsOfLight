#pragma once

#include <vector>
#include <memory>

#include "Component.hpp"

class GameObject{

    std::vector<std::unique_ptr<Component>> m_components;

public:

    GameObject() { }

    void add_component(std::unique_ptr<Component> component);
    Component& get_component(int /*What use here?*/ component_type);

};