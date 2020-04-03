//
// Created by danie on 3-4-2020.
//

#include "RNG.h"
#include <random>

namespace dasl
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<> distr(0, 1);
}
