#include "System.hpp"
#include <chrono>
#include "Entity.hpp"

System::System (Game &game, std::string name) : m_pgame(game), m_name(name) { }
System::~System() { }
bool System::has_valid_signature(const Entity &entity){ return entity.contains_signature(m_signature); }

std::string System::get_name() { return m_name; }
Timing System::get_timing() { return m_timing; }

void System::update_timed(double dT){
    // We're going to keep track of how long these functions take.

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
    auto start = clock::now();


    update(dT);


    sec duration = clock::now() - start;
    m_timing.update_timing(duration.count());
}