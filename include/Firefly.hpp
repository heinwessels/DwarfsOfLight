#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Component.hpp"
#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "CollisionBoxComponent.hpp"
#include "MoveComponent.hpp"

class Firefly : public Entity{

private:
    double width = 0.5;
    double height = 0.5;

public:
    Firefly(double x, double y) : Entity("Firefly") {
        this->add_component<TransformComponent>(Vec2(x, y));
        this->add_component<SporadicMoveComponent>(3, 6, 0.2);
        this->add_component<Renderable>("textures/firefly_simple.jpg", width, height, 3, 3, 1, 1);
        this->add_component<CollisionBox>(width, height);
        this->add_component<PathfindingComponent>();
        this->add_component<AIComponent>(AIComponent::ModeWandering);
        this->add_component<LightComponent>(MColour(100, 150, 250), MColour(10, 10, 10), 1, 5);
    }
};