#include <iostream>

#include "Cell.h"
#include "FileWriter.h"
#include <ctime>
#include <math.h>

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

void print_timestamp(){
    time_t now = time(0);
    char* dt = ctime(&now);
    std::cout << "timestamp at: " << dt << "\n";
}

int main() {
    bool timestep = false;
    bool eventdrive = true;
    bool write_timestep = false;
    bool write_eventdrive = true;
    double bplpt[20];// = {0.00000000, 0.00000005, 0.00000008, 0.00000010, 0.00000011, 0.000000115, 0.00000012, 0.000000125, 0.00000013, 0.00000014, 0.00000015, 0.00000016, 0.00000017, 0.00000018, 0.00000019, 0.00000020, 0.00000021, 0.00000023, 0.00000025, 0.00000030};
    double bpnpt[20];
    int count[20];
    for(int b = 0; b < 20; b++) {
        count[0] = 0;
        bplpt[b] = 0.000000015*b;
        bpnpt[b] = 0.0000000000000001*pow(10, b*1.0);
    }
    FileWriter countwriter = FileWriter("speed_counts");
    countwriter.writeParameters(bpnpt[0]);

    //std::cout << std::to_string(1.0/.00) <<"\n";
    print_timestamp();
    std::cout << "start timestep driven \n";

    if(timestep) {
    for(int r = 0; r < 20; r++){
//        int n_bins = 101;
//        int bins[n_bins];
//        for(int b = 0; b < n_bins; b++){
//            bins[b] = 0;
//        }


            int t_max = 10000;
            double lengths_per_timestep[N_MICROTUBULES];
            int states_per_timestep[N_MICROTUBULES];
            for (int cell_run = 0; cell_run < 1; cell_run++) {
                Cell cell1 = Cell(bplpt[r]);

                for (int i = 0; i < t_max; i++) {
                    cell1.run_timestep();
                    count[r] += 1;
//                    if (i > 50000) {
//                        bins[(int) (cell1.get_polarity() * n_bins)]++;
//                    }

                }
                //printProgress((double) cell_run / 100.0);
            }
            //printProgress(1);
            //std::cout << "\n";
            if (write_timestep) {
                FileWriter polarity = FileWriter("MT_polarity");
                polarity.writeParameters(bplpt[r]);
                //polarity.writeIntArray(bins, n_bins);
            }
        //std::cout << std::to_string(bins[50]) <<"\n";
    }//end run

    print_timestamp();
    std::cout << "start event driven \n";
    }
    if(eventdrive){
        double total_time = 10000000.0;
        for(int s = 0; s < 20; s++) {
            int n_bins = 301;
            int bins[n_bins];
            for(int b = 0; b < n_bins; b++){
                bins[b] = 0;
            }
            //std::cout << std::to_string(s)<<  "\n";
            Cell cell2;
            for (int cell_run = 0; cell_run < 1; cell_run++) {
                cell2 = Cell(bpnpt[s], total_time, NUMBER);
                bool next = true;
                while (next) {
                    count[s] += 1;
                    next = cell2.run_event();
                    bins[(int) (cell2.get_polarity() * n_bins)]++;
                }
            }
            if (write_eventdrive) {
                FileWriter polarity = FileWriter("MT_polarity");
                polarity.writeParameters(bpnpt[s]);
                polarity.writeIntArray(bins, n_bins);
            }

        }
    }

    print_timestamp();
    countwriter.writeIntArray(count, 20);
    return 0;
}



