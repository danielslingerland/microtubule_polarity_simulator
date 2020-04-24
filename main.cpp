#include <iostream>

#include "Cell.h"
#include "FileWriter.h"

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
    double bplpt[] = {0.00000000, 0.00000005, 0.0000008, 0.0000010, 0.0000011, 0.00000115, 0.0000012, 0.00000125, 0.0000013, 0.0000014, 0.0000015, 0.0000016, 0.0000017, 0.0000018, 0.0000019, 0.0000020, 0.0000021, 0.0000023, 0.0000025, 0.0000030};
    for(int r = 0; r < 20; r++){
        FileWriter polarity = FileWriter("MT_polarity");
        polarity.writeParameters(bplpt[r]);
//    FileWriter state = FileWriter("MT_state2");
//    state.writeParameters();

        int t_max = 1000000;
//    double lengths_per_timestep[N_MICROTUBULES];
//    int states_per_timestep[N_MICROTUBULES];
        for(int cell_run = 0; cell_run < 100; cell_run++) {
            Cell cell1 = Cell(bplpt[r]);

            for (int i = 0; i < t_max; i++) {
                cell1.run_timestep();
                if (i > 50000) {
                    polarity.writeDouble(cell1.get_polarity());
                }

            }
            printProgress((double) cell_run / 100.0);
        }
        printProgress(1);
        std::cout << "\n";
    }//end run

    return 0;
}



