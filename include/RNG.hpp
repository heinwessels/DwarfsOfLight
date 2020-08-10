#pragma once

#include <random>

static float random_float_in_range(float a, float b) { return ((b - a) * ((float)rand() / RAND_MAX)) + a; }