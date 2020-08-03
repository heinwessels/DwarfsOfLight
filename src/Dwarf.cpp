#include "Dwarf.hpp"

#include "Vec2.hpp"
#include "MoveComponent.hpp"
#include "Renderable.hpp"
#include "ControllerComponent.hpp"

Dwarf::Dwarf(SDL_Texture* texture, float x, float y){
    this->add_component(std::make_unique<MoveComponent>(Vec2(x, y), Vec2(0.0f, 0.0f)));
    this->add_component(std::make_unique<Renderable>(texture, width, height));
    this->add_component(std::make_unique<ControllerComponent>(10));
}