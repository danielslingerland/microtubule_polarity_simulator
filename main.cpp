#include <iostream>

#include "Cell.h"
#include "FileWriter.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress (double progress)
{
    int barWidth = 70;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}


int main() {

    FileWriter polarity = FileWriter("MT_polarity");
    polarity.writeParameters();
//    FileWriter state = FileWriter("MT_state2");
//    state.writeParameters();

    int t_max = 10000000;
//    double lengths_per_timestep[N_MICROTUBULES];
//    int states_per_timestep[N_MICROTUBULES];
    Cell cell1 = Cell();
    for (int i = 0; i < t_max; i++) {
        cell1.run_timestep();
        if (i % 10000 == 0) {
            printProgress( (double) i / (double) t_max );
        }
        if (i > 50000) {
            polarity.writeDouble(cell1.get_polarity());
        }

    }


    return 0;
}



