#include "System.hpp"

void System::update_timed(double dT){
    // We're going to keep track of how long these functions take.

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
    auto start = clock::now();


    update(dT);


    sec duration = clock::now() - start;
    m_timing.update_timing(duration.count());
}