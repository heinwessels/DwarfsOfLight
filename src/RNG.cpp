#include "RNG.hpp"

double random_float_in_range(double a, double b) { return ((b - a) * ((double)rand() / RAND_MAX)) + a; }