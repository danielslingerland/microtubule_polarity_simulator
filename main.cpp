#include <iostream>
#include <random>
#include "Microtubule.h"
#include "RNG.h"
#include "Cell.h"
#include "FileWriter.h"
#include<string>

#include <fstream>


int main() {


    FileWriter polarity = FileWriter("MT_polarity");
    polarity.writeParameters();
//    FileWriter state = FileWriter("MT_state2");
//    state.writeParameters();

    int t_max = 100000;
//    double lengths_per_timestep[N_MICROTUBULES];
//    int states_per_timestep[N_MICROTUBULES];
    Cell cell1 = Cell();
    for (int i = 0; i < t_max; i++) {
        cell1.run_timestep();
        if (i % 10000 == 0) {
            std::cout << (double) i / (double) t_max << "   " << cell1.get_polarity() << "\n";
        }
        if (i > 50000) {
            polarity.writeDouble(cell1.get_polarity());
        }

    }


    return 0;
}



