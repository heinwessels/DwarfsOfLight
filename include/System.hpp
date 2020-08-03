#pragma once

#include "Types.hpp"
#include "Entity.hpp"

class Game;
class System{

protected:
    Game &m_pgame;
    ComponentListSignature m_signature = 0;

public:
    System (Game &game) : m_pgame(game) { }
    virtual ~System() { };
    virtual void update(float dT) = 0;
    bool has_valid_signature(const Entity &entity){ return entity.contains_signature(m_signature); }
};
