#include <iostream>
#include <random>
#include "Microtubule.h"
#include "RNG.h"


int main() {
    //random number generation

    //std::uniform_real_distribution<> distr(0, 1); // define the range
    //Microtubule first_mt = Microtubule();
   // std::cout << "microtubules length: " << std::to_string(first_mt.get_length());
    //std::uniform_real_distribution<> distr(0, 1); // define the range
    for(int i = 0; i < 100; i++) {
        std::cout << dasl::distr(dasl::rng) << std::endl;
    }

        //first_mt.process();
        //std::cout << "\nmicrotubules length: " << std::to_string(first_mt.get_length());
   // }
    //Microtubule second_mt = Microtubule();
    return 0;
}

