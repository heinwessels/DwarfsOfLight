#pragma once

#include <memory>

#include "Entity.hpp"

#include "Component.hpp"
#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "LightComponent.hpp"
#include "ControllerComponent.hpp"
#include "MoveComponent.hpp"
#include "TeamComponent.hpp"

class Dwarf : public Entity{

private:
    double width = 1;
    double height = 1;

public:
    Dwarf(double x, double y) : Entity("Dwarf") {
        this->add_component<TransformComponent>(Vec2(x, y));
        this->add_component<ControllerComponent>();
        this->add_component<MoveComponent>(MoveComponent::TypeStraight, 5);
        this->add_component<Renderable>("textures/dwarf2.jpg", width, height);

        this->add_component<LightComponent>(MColour(230, 150, 150), MColour(20, 20, 0), 1, 10);
        this->add_component<CollisionBox>(width, height);
        // this->add_component<TeamComponent>(TeamDwarf,
        //     std::vector<TeamComponent::TeamID>({}),
        //     std::vector<TeamComponent::TeamID>({TeamGoblin}),
        //     0.0
        // );
    }
};