#include <iostream>

#include "Cell.h"
#include "FileWriter.h"
#include <ctime>

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
    double bplpt[] = {0.00000000, 0.00000005, 0.00000008, 0.00000010, 0.00000011, 0.000000115, 0.00000012, 0.000000125, 0.00000013, 0.00000014, 0.00000015, 0.00000016, 0.00000017, 0.00000018, 0.00000019, 0.00000020, 0.00000021, 0.00000023, 0.00000025, 0.00000030};

    //std::cout << std::to_string(1.0/.00) <<"\n";
    print_timestamp();
    std::cout << "start timestep driven \n";

    int count = 0;
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
                    count += 1;
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
    std::cout << "end timestep driven run "<< std::to_string(count) <<" steps \n";
    print_timestamp();
    count = 0;
    std::cout << "start event driven \n";
    }
    if(eventdrive){
        double total_time = 1000000.0;
        for(int s = 0; s < 20; s++) {
            int n_bins = 301;
            int bins[n_bins];
            for(int b = 0; b < n_bins; b++){
                bins[b] = 0;
            }
            //std::cout << std::to_string(s)<<  "\n";
            for (int cell_run = 0; cell_run < 1; cell_run++) {
                Cell cell2 = Cell(bplpt[s], total_time);
                bool next = true;
                while (next) {
                    count += 1;
                    next = cell2.run_event();
                    bins[(int) (cell2.get_polarity() * n_bins)]++;
                }
            }
            if (write_eventdrive) {
                FileWriter polarity = FileWriter("MT_polarity");
                polarity.writeParameters(bplpt[s]);
                polarity.writeIntArray(bins, n_bins);
            }

        }
    }
    std::cout << "end event driven run "<< std::to_string(count) <<" events \n";
    print_timestamp();
    return 0;
}



