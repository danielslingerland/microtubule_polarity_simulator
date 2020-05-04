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
    double bplpt[] = {0.00000000, 0.00000005, 0.00000008, 0.00000010, 0.00000011, 0.000000115, 0.00000012, 0.000000125, 0.00000013, 0.00000014, 0.00000015, 0.00000016, 0.00000017, 0.00000018, 0.00000019, 0.00000020, 0.00000021, 0.00000023, 0.00000025, 0.00000030};
    for(int r = 0; r < 20; r++){
        int n_bins = 101;
        int bins[n_bins];
        for(int b = 0; b < n_bins; b++){
            bins[b] = 0;
        }

//    FileWriter state = FileWriter("MT_state2");
//    state.writeParameters();

        int t_max = 100000;
//    double lengths_per_timestep[N_MICROTUBULES];
//    int states_per_timestep[N_MICROTUBULES];
        for(int cell_run = 0; cell_run < 10; cell_run++) {
            Cell cell1 = Cell(bplpt[r]);

            for (int i = 0; i < t_max; i++) {
                cell1.run_timestep();
                if (i > 50000) {
                     bins[(int) (cell1.get_polarity()*n_bins)]++;
                }

            }
            printProgress((double) cell_run / 100.0);
        }
        printProgress(1);
        std::cout << "\n";
        FileWriter polarity = FileWriter("MT_polarity");
        polarity.writeParameters(bplpt[r]);
        polarity.writeIntArray(bins, n_bins);
    }//end run

    return 0;
}



