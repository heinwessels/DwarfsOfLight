#pragma once

#include <unistd.h>

#include "Game.hpp"

class Application{

    Game m_game;

public:

    Application();
    void run();
};