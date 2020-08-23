#pragma once

#include <vector>
#include "Component.hpp"

class LifeComponent : public Component{
public:
    static constexpr ComponentID ID = LifeComponentID;

    double health;

    double food = 0;
    double food_consumption_rate = 0;   // per second

    bool can_reproduce = false;
    bool need_mate_to_reproduce = false;
    double reproduce_every = 0;

    bool can_die_of_age = false;
    double time_till_death = 0;

    LifeComponent(double health) : Component(ID), health(health) { }
};


class AnimalLifeComponent : public LifeComponent{
public:
    AnimalLifeComponent(double health, double food_consumption_rate, double reproduce_every, double lifetime)
        : LifeComponent(health)
    {
        this->reproduce_every = reproduce_every;
        this->food_consumption_rate = food_consumption_rate;
        food = food_consumption_rate * 60;  // Can survive for 1 minute from birth TODO Configurable

        can_reproduce = true;
        need_mate_to_reproduce = true;

        time_till_death = lifetime;
    }
};