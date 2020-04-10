//
// Created by danie on 3-4-2020.
//

#include "RNG.h"
#include <random>
#include <iostream>
#include <time.h>


namespace dasl
{
    //std::mt19937 rng(std::random_device{}());
    std::mt19937 rng(time(0));

    std::uniform_real_distribution<> distr(0, 1);
    std::function<double (void)> mt_rng = std::bind(distr,rng);
}
