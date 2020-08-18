#pragma once

#include <string>

#include "Timing.hpp"
#include "Types.hpp"

class Entity;
class Game;
class System{

protected:
    Game &m_pgame;
    ComponentListSignature m_signature = 0;
    std::string m_name;
    Timing m_timing;

public:
    System (Game &game, std::string name);
    virtual ~System();
    void update_timed(double dT);
    bool has_valid_signature(const Entity &entity);

    virtual void init() = 0;
    virtual void update(double dT) = 0;

    std::string get_name();
    Timing get_timing();
};
