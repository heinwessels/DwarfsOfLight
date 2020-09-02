#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Component.hpp"
#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "CollisionBoxComponent.hpp"
#include "MoveComponent.hpp"
#include "TeamComponent.hpp"
#include "LifeComponent.hpp"
#include "PathfindingComponent.hpp"
#include "AIComponent.hpp"

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
        this->add_component<AIComponent>();
        this->add_component<LightComponent>(MColour(100, 150, 250), MColour(10, 10, 10), 1, 5);

        // this->add_component<TeamComponent>(TeamBug,
        //     std::vector<TeamComponent::TeamID>({TeamGoblin}),
        //     std::vector<TeamComponent::TeamID>({TeamPlant}),
        //     4.0, 7.0, 3.0
        // );
        // this->add_component<AnimalLifeComponent>(LifeComponent::TypeBug, 30, 3, 0);
    }
};