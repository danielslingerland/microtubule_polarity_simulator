//
// Created by danie on 3-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_CELL_H
#define MICROTUBULE_POLARITY_SIMULATOR_CELL_H


#include "Microtubule.h"


class Cell {
private:
    const double SECOND_METER = 80000.0;

    double l_right;
    double l_left;
    double halftime(double length);
    void check_binding(int n);

public:
    Microtubule MiTus[N_MICROTUBULES];
    Cell();
    void run_timestep();
    double get_polarity();
    double get_average_lenth();
    double polarity_numbers();


};


#endif //MICROTUBULE_POLARITY_SIMULATOR_CELL_H
