#include "Dwarf.hpp"

#include "RenderSystem.hpp"

Dwarf::Dwarf(float x, float y, SDL_Texture* texture){

    this->m_renderable = std::make_unique<Renderable>(texture);

}