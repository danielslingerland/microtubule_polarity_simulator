#include <iostream>
#include <random>
#include "Microtubule.h"
#include "RNG.h"
#include "Cell.h"


int main() {

    Cell cell1 = Cell();
    for(int i = 0; i < 10000; i++) {
        cell1.run_timestep();
        if(i%100 == 0) {
            std::cout << cell1.get_polarity() << "    "<< cell1.get_average_lenth() << "\n";
        }
        //std::cout << i << "\n";
    }

    return 0;
}

