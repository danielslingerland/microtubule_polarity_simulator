//
// Created by danie on 2-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
#define MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
#include "Parameters.h"
#include "RNG.h"
class Microtubule{

private:
    int n_guests;
    double length;
    double min_length_t_step;
    double t_event;
    bool event;
    bool side;
    int state;
    Microtubule* host;
    double bind_pos;




public:

    Microtubule();
    Microtubule(bool r);
    void reset(double l,bool r);
    void process();
    void bind_to_at(Microtubule* host_mt, double pos);
    double get_length();
    double get_min_length_t_step();
    double get_t_event();
    int get_state();
    bool get_side();
    bool get_event();
    void set_event(bool e);
    void check_host_length();
    void add_guest();
    void delete_guest();

};


#endif //MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
