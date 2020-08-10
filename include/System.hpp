#pragma once

#include <string>
#include <chrono>

#include "Timing.hpp"
#include "Types.hpp"
#include "Entity.hpp"

class Game;
class System{

protected:
    Game &m_pgame;
    ComponentListSignature m_signature = 0;
    std::string m_name;

    Timing m_timing;

public:
    System (Game &game, std::string name) : m_pgame(game), m_name(name) { }
    virtual ~System() { };
    void update(double dT);
    virtual void internal_update(double dT) = 0;
    bool has_valid_signature(const Entity &entity){ return entity.contains_signature(m_signature); }

    std::string get_name() { return m_name; }
    Timing get_timing() { return m_timing; }
};
