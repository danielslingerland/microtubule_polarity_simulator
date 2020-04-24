//
// Created by danie on 3-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_CELL_H
#define MICROTUBULE_POLARITY_SIMULATOR_CELL_H


#include "Microtubule.h"


class Cell {
private:
    double BINDING_PER_LENGTH_PER_TIME;
    double l_right;
    double l_left;
    static double halftime(double length);
    bool check_binding(int n);
    Microtubule MiTus[N_MICROTUBULES];

public:

    Cell(double bplpt);
    void run_timestep();
    double get_polarity();
    double get_average_lenth();
    double polarity_numbers();


};


#endif //MICROTUBULE_POLARITY_SIMULATOR_CELL_H
