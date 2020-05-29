//
// Created by danie on 3-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_CELL_H
#define MICROTUBULE_POLARITY_SIMULATOR_CELL_H


#include "Microtubule.h"


class Cell {
private:
    double r_binding;
    double l_right;
    double l_left;
    double run_time;
    int type;
    bool check_binding(int n);
    void update_total_lengths();
    Microtubule MiTus[N_MICROTUBULES];
public:
    Cell();
    Cell(double bplpt);
    Cell(double bplpt, double rt, int type = LENGTH);
    void run_timestep();
    double get_polarity();
    double get_average_lenth();
    double polarity_numbers();
    double halftime(double length);
    bool run_event();
    double get_runtime();




};


#endif //MICROTUBULE_POLARITY_SIMULATOR_CELL_H
