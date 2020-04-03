//
// Created by danie on 3-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_CELL_H
#define MICROTUBULE_POLARITY_SIMULATOR_CELL_H


#include "Microtubule.h"

class Cell {
private:
    int N_MICROTUBULES = 1000;
    const double SECOND_METER = 0.5;
    Microtubule MiTus[1000];
    double p_right;
    double l_right;
    double l_left;
public:
    Cell(double p_r);
    void set_p_right(double p_r);
    void run_timestep(double t_step);
    double halftime(double length);
    void check_binding(int n, double t_step);


};


#endif //MICROTUBULE_POLARITY_SIMULATOR_CELL_H
