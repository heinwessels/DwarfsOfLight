#pragma once

#include <vector>
#include "Component.hpp"
#include "RNG.hpp"

class LifeComponent : public Component{
public:
    static constexpr ComponentID ID = LifeComponentID;

    double health;

    double food = 0;
    double food_consumption_rate = 0;   // per second

    bool can_reproduce = false;         // Toggle if can reproduce
    bool ready_to_reproduce = false;    // Flag for when this component can reproduce
    bool need_mate_to_reproduce = false;
    double reproduce_every = 0;         // Every how many seconds
    double time_till_reproduce = 0;
    int max_number_of_offspring = 1;
    double reproduce_minimum_food = 10;

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
        time_till_reproduce = reproduce_every * random_float_in_range(0.8, 1.5);

        // can_die_of_age = age;
        time_till_death = lifetime;
    }
};

class BugLifeComponent : public LifeComponent{
public:
    BugLifeComponent(double health, double food_consumption_rate, double reproduce_every, double lifetime)
        : LifeComponent(health)
    {
        this->reproduce_every = reproduce_every;
        this->food_consumption_rate = food_consumption_rate;
        food = food_consumption_rate * 60;  // Can survive for 1 minute from birth TODO Configurable

        can_reproduce = true;
        max_number_of_offspring = 3;
        time_till_reproduce = reproduce_every * random_float_in_range(0.8, 1.5);

        // can_die_of_age = age;
        time_till_death = lifetime;
    }
};

class PlantLifeComponent : public LifeComponent{
public:
    PlantLifeComponent(double health, double food_value, double reproduce_every)
        : LifeComponent(health)
    {
        this->reproduce_every = reproduce_every;
        this->food = food_value;

        can_reproduce = true;
        max_number_of_offspring = 3;
        time_till_reproduce = reproduce_every * random_float_in_range(0.8, 1.5);
    }
};