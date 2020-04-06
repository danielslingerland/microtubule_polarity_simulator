#include <iostream>
#include <random>
#include "Microtubule.h"
#include "RNG.h"
#include "Cell.h"


int main() {

    Cell cell1 = Cell(0.50);
    for(int i = 0; i < 10000; i++) {
        cell1.run_timestep(1);
        if(i%1000 == 0) {
            std::cout << cell1.get_polarity() << "    "<< cell1.get_average_lenth() << "\n";
        }
        //std::cout << i << "\n";
    }

    return 0;
}

