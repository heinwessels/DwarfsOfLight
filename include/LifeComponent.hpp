#pragma once

#include <vector>
#include "Component.hpp"
#include "RNG.hpp"
#include "NamedType.hpp"

class LifeComponent : public Component{
public:
    static constexpr ComponentID ID = LifeComponentID;

    typedef int Type;
    Type type;
    static constexpr Type TypeFungi = 0;
    static constexpr Type TypeBug = 0;
    static constexpr Type TypeGoblin = 0;
    using CreateTypeFungi = UniqueType<struct TypeFungiPhantom>;
    using CreateTypeBug = UniqueType<struct TypeBugPhantom>;
    using CreateTypeGoblin = UniqueType<struct TypeGoblinPhantom>;

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

private:
    LifeComponent(Type type, double health) : Component(ID), type(type), health(health) { }

public:
    LifeComponent(CreateTypeFungi t, double health, double food_value, double reproduce_every)
        : LifeComponent(TypeFungi, health)
    {
        this->reproduce_every = reproduce_every;
        this->food = food_value;

        can_reproduce = true;
        max_number_of_offspring = 3;
        time_till_reproduce = reproduce_every * random_float_in_range(0.8, 1.5);
    }

    LifeComponent(CreateTypeBug t, double health, double food_consumption_rate, double reproduce_every, double lifetime)
        : LifeComponent(TypeBug, health)
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

    LifeComponent(CreateTypeGoblin t, double health, double food_consumption_rate, double reproduce_every, double lifetime)
        : LifeComponent(TypeGoblin, health)
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