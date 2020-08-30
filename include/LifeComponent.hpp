#pragma once

#include <vector>
#include "Component.hpp"
#include "RNG.hpp"

class LifeComponent : public Component{
public:
    static constexpr ComponentID ID = LifeComponentID;

    typedef int Type;
    Type type;
    static constexpr Type TypeNone = 0; // For reproduction/on-death spawning
    static constexpr Type TypeFungi = 1;
    static constexpr Type TypeBug = 2;
    static constexpr Type TypeGoblin = 3;


    double energy;
    double energy_consumption_rate = 0;     // Per second

    bool can_reproduce = false;
    double reproduce_every = 0;  // How long before can reproduce
    double reproduction_time_until = 0;
    double reproduction_energy = 0; // How much energy does it cost to reproduce. (Needs at least 2*this)
    int reproduction_max_neighbours = 1e6;

protected:
    LifeComponent(Type type, double energy) : Component(ID), type(type), energy(energy) { }
};

class FungiLifeComponent : public LifeComponent{
public:
    FungiLifeComponent(double energy, double reproduce_every, int reproduction_max_neighbours)
        : LifeComponent(TypeFungi, energy)
    {
        can_reproduce = true;
        this->reproduce_every = reproduce_every;
        reproduction_time_until = reproduce_every;
        this->reproduction_max_neighbours = reproduction_max_neighbours;
    }
};

class AnimalLifeComponent : public LifeComponent{
public:
    AnimalLifeComponent(Type type, double energy, double energy_consumption, double reproduce_every)
        : LifeComponent(type, energy)
    {
        this->energy_consumption_rate = energy_consumption;

        can_reproduce = true;
        this->reproduce_every = reproduce_every;
        reproduction_time_until = reproduce_every;
        this->reproduction_energy = energy; // The starting energy must be equal to energy required to give birth
    }
};
