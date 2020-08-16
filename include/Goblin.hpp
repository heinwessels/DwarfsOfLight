#pragma once

#include <memory>
#include <string>

#include "Entity.hpp"

#include "Renderable.hpp"
#include "TransformComponent.hpp"
#include "CollisionBoxComponent.hpp"
#include "PathfindingComponent.hpp"

class Goblin : public Entity{

private:
    double width = 1;
    double height = 1;
    std::string m_texture_path = "textures/goblin.jpg";

public:
    Goblin(double x, double y) : Entity("Goblin") {
        this->add_component(std::make_unique<TransformComponent>(Vec2(x, y)));
        this->add_component(std::make_unique<Renderable>(m_texture_path, width, height));
        this->add_component(std::make_unique<CollisionBox>(width, height, false, false));
        this->add_component(std::make_unique<LightComponent>(
            MColour(0, 200, 100, 0), MColour(0, 50, 30), 1, 4
        ));

        this->add_component(std::make_unique<PathfindingComponent>());
    }
};