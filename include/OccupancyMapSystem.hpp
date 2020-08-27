#pragma once
/*
    There is too much proximity checks, especially
    during the life system. Therefore I'm saving
    on which tile every entity lives for the
    current update.
*/

#include "System.hpp"
#include "Vec2.hpp"

#include <vector>
#include <list>

class World;
class OccupancyMap{
    int m_width, m_height;

    // Storing list of references per tile,
    // because I don't want raw pointers
    // Yeah, it's rough
    using OccupancyMap_t = std::vector<
                    std::vector<
                        std::list<
                            Entity*
                        >
                    >
                >;
    OccupancyMap_t m_map;

public:
    OccupancyMap(int width, int height);
    OccupancyMap_t &get_map() { return m_map; }
    int get_width() { return m_width; }
    int get_height() { return m_height; }

    void clear();
    void resize(int width, int height);

    std::list<Entity*> find_entities_in_range(World &world, Vec2 position, Vec2 range);
};

class Game;
class OccupancySystem : public System {

public:
    OccupancySystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;
};