#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "CollisionBoxComponent.hpp"
#include "PathfindingComponent.hpp"
#include "AIComponent.hpp"
#include "MoveComponent.hpp"
#include "TeamComponent.hpp"

class Goblin : public Entity{

private:
    double width = 0.8;
    double height = 0.8;
    std::string m_texture_path = "textures/goblin.jpg";

public:
    Goblin(double x, double y) : Entity("Goblin") {
        this->add_component<TransformComponent>(Vec2(x, y));
        this->add_component<MoveComponent>(MoveComponent::TypeStraight, 5);
        this->add_component<Renderable>(m_texture_path, width, height);
        this->add_component<CollisionBox>(width, height, false, false);
        this->add_component<PathfindingComponent>();
        this->add_component<AIComponent>();

        this->add_component<TeamComponent>(TeamGoblin,
            std::vector<TeamComponent::TeamID>(TeamBug),
            std::vector<TeamComponent::TeamID>(TeamDwarf),
            0.0
        );
    }
};