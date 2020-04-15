#include <iostream>
#include <random>
#include "Microtubule.h"
#include "RNG.h"
#include "Cell.h"
#include "FileWriter.h"
#include<string>

#include <fstream>


int main() {


    FileWriter length = FileWriter("MT_length2");
    length.writeParameters();
    FileWriter state = FileWriter("MT_state2");
    state.writeParameters();

    int t_max = 100000;
    double lengths_per_timestep[N_MICROTUBULES];
    int states_per_timestep[N_MICROTUBULES];
    Cell cell1 = Cell();
    for(int i = 0; i < t_max; i++) {
        cell1.run_timestep();
        if(i%10000 == 0) {
            std::cout << (double) i/ (double) t_max << "\n";
        }
        if(i > 10000) {

            for (int m = 0; m < N_MICROTUBULES; m++) {

                lengths_per_timestep[m] = cell1.MiTus[m].get_length();
                states_per_timestep[m] = cell1.MiTus[m].get_state();
            }
            length.writeDoubleArray(lengths_per_timestep, N_MICROTUBULES);
            state.writeIntArray(states_per_timestep, N_MICROTUBULES);
        }

    }

    return 0;
}



