//
// Created by danie on 3-4-2020.
//

#include "Cell.h"
#include "RNG.h"

Cell::Cell(){
    for(int n = 0; n < N_MICROTUBULES; n++){
        MiTus[n] = Microtubule(dasl::distr(dasl::rng) < P_RIGHT);

    }

}

void Cell::run_timestep(){

    //.............Calculating the total length of both sides......................
    l_left  = 0;
    l_right = 0;
    for(int n = 0; n < N_MICROTUBULES; n++){
        if(MiTus[n].get_side() == RIGHT){
            l_right += MiTus[n].get_length();
        }else{
            l_left  += MiTus[n].get_length();
        }
    }


    //.............Processing growth, shrinkage, (un)binding, nucleation.............
    for(int n = 0; n < N_MICROTUBULES; n++){
        //ONE EVENT (catstrophe, rescue, bidning, unbinding) per timestep

        //growing, shrinking processes & catastrophe, rescue, unbinding events.
        MiTus[n].process();

        //bidning events, unbinding events as a result of host length, deletion as result of lenght < 0
        if(MiTus[n].get_state() == GROWING) {
            check_binding(n);
        }else if(MiTus[n].get_state() == BOUND){
            MiTus[n].check_host_length();
        }else if(MiTus[n].get_length() < 0){
            MiTus[n] = Microtubule(dasl::distr(dasl::rng) < P_RIGHT);
        }
    }

}

void Cell::check_binding(int n){
    double length = 0;
    if(MiTus[n].get_side() ==  RIGHT){
        length = l_left;  //length of opposing microtubules
    }else{
        length = l_right; //length of opposing microtubules
    }
    std::uniform_real_distribution<> distr_rl(0, length);
    double p_bind = 1-exp(-T_STEP/halftime(length));

    if(dasl::distr(dasl::rng) < p_bind){
        double global_pos = distr_rl(dasl::rng);
        bool searching = true;
        int s = 0;
        while(searching){
            if(MiTus[s].get_side() != MiTus[n].get_side()) {
                if (global_pos - MiTus[s].get_length() >= 0) {
                    global_pos -= MiTus[s].get_length();
                    s += 1;
                } else {
                    searching = false;
                }
            }else{
                s += 1;
            }
        }
        MiTus[n].bind_to_at(&MiTus[s], global_pos);
    }
};

double Cell::halftime(double length){
    return SECOND_METER/length;
}


double Cell::get_polarity() {
    return l_right/(l_left+l_right);
}
double Cell::get_average_lenth(){
    return (l_left+l_right)/1000;
}