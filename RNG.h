//
// Created by danie on 3-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_RNG_H
#define MICROTUBULE_POLARITY_SIMULATOR_RNG_H
#include <random>

namespace dasl
{

    extern std::mt19937 rng;
    extern std::uniform_real_distribution<> distr;

}


#endif //MICROTUBULE_POLARITY_SIMULATOR_RNG_H
