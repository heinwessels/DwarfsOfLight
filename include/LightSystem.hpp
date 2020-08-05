#pragma once

#include "System.hpp"
#include "Renderer.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"

class Game;
class LightSystem : public System{

public:
    LightSystem(Game &game);
    virtual void update(float dT) override;
};

