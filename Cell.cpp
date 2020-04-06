//
// Created by danie on 3-4-2020.
//

#include "Cell.h"
#include "Microtubule.h"
#include "RNG.h"

Cell::Cell(double p_r){
    p_right = p_r;
    for(int n = 0; n < N_MICROTUBULES; n++){
        MiTus[n] = Microtubule(dasl::distr(dasl::rng) < p_right);

    }

}

void Cell::run_timestep(double t_step){

    //.............Calculating the total length of both sides......................
    l_left  = 0;
    l_right = 0;
    for(int n = 0; n < N_MICROTUBULES; n++){
        if(MiTus[n].is_right()){
            l_right += MiTus[n].get_length();
        }else{
            l_left  += MiTus[n].get_length();
        }
    }


    //.............Processing growth, shrinkage, (un)binding, nucleation.............
    for(int n = 0; n < N_MICROTUBULES; n++){
        //ONE EVENT (catstrophe, rescue, bidning, unbinding) per timestep

        //growing, shrinking processes & catastrophe, rescue, unbinding events.
        MiTus[n].process(t_step);

        //unbinding events as a result of host length.
        if(MiTus[n].is_bound()){
            MiTus[n].check_host_length(t_step);
        }

        //bidning events, just unbound microtubules cannot bind due to shrinking.
        if(MiTus[n].is_growing()) {
            check_binding(n, t_step);
        }



        if(MiTus[n].get_length() < 0){
            MiTus[n] = Microtubule(dasl::distr(dasl::rng) < p_right);
        }
    }

}

void Cell::check_binding(int n, double t_step){
    double length = 0;
    if(MiTus[n].is_right()){
        length = l_left;
    }else{
        length = l_right;
    }
    std::uniform_real_distribution<> distr_rl(0, length);
    double p_bind = 1-exp(-t_step/halftime(length));

    if(dasl::distr(dasl::rng) < p_bind){
        double global_pos = distr_rl(dasl::rng);
        bool searching = true;
        int s = 0;
        while(searching){
            if(MiTus[s].is_right() != MiTus[n].is_right()) {
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
        MiTus[n].bind(&MiTus[s], global_pos);
    }
};

double Cell::halftime(double length){
    return SECOND_METER/length;
}

void Cell::set_p_right(double p_r){
    p_right = p_r;
}

double Cell::get_polarity() {
    return l_right/(l_left+l_right);
}
double Cell::get_average_lenth(){
    return (l_right+l_right)/1000;
}