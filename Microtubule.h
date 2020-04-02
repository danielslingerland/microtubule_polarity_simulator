//
// Created by danie on 2-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
#define MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H


class Microtubule{

private:
    double length;
    int state;
    bool growing;
    bool bound;
    Microtubule* host;
    double bind_pos;
    constexpr static double GROWSPEED = 1;
    constexpr static double SHRINKSPEED = 5;
    constexpr static double P_UNBIND = 0.5;
    constexpr static double P_CATASTROPHE = 0.04;
    constexpr static double P_RESCUE = 0.04;



public:

    Microtubule();
    Microtubule(double l, bool g, bool b);
    void process();
    void bind(Microtubule* host_mt, double pos);
    double get_length();
    bool is_growing();
    bool is_bound();
};


#endif //MICROTUBULE_POLARITY_SIMULATOR_MICROTUBULE_H
