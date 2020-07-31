#include "Dwarf.hpp"

#include "MoveComponent.hpp"
#include "Renderable.hpp"

Dwarf::Dwarf(SDL_Texture* texture){
    this->add_component(std::make_unique<MoveComponent>());
    this->add_component(std::make_unique<Renderable>(texture));
}