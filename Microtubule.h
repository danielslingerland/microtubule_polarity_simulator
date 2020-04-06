//
// Created by danie on 2-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
#define MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H


class Microtubule{

private:
    double length;
    double min_length_t_step;
    double t_event;
    bool growing;
    bool bound;
    bool right_side; // right = true, left = false
    Microtubule* host;
    double bind_pos;
    constexpr static double GROWSPEED = 1;
    constexpr static double SHRINKSPEED = 5;
    constexpr static double P_UNBIND = 0.5;
    constexpr static double P_CATASTROPHE = 0.05;
    constexpr static double P_RESCUE = 0.04;



public:

    Microtubule();
    Microtubule(bool r);
    Microtubule(double l, bool g, bool b, bool r);
    void process(double t_step);
    void bind(Microtubule* host_mt, double pos);
    double get_length();
    double get_min_length_t_step();
    double get_t_event();
    bool is_growing();
    bool is_bound();
    bool is_right();
    void check_host_length(double t_step);

};


#endif //MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
