#pragma once

#include <unistd.h>
#include <chrono>

#include "Game.hpp"

class Application{

    Game m_game;

public:

    Application();
    void run();
};