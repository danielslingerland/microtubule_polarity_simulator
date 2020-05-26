//
// Created by danie on 3-4-2020.
//

#include "Cell.h"


Cell::Cell(double bplpt){
    BINDING_PER_LENGTH_PER_TIME = bplpt;
    for(int n = 0; n < N_MICROTUBULES; n++){
        MiTus[n] = Microtubule(dasl::mt_rng() < P_RIGHT);

    }

}

Cell::Cell(double bplpt, double rt){
    run_time = rt;
    BINDING_PER_LENGTH_PER_TIME = bplpt;
    for(int n = 0; n < N_MICROTUBULES; n++){
        MiTus[n] = Microtubule(dasl::mt_rng() < P_RIGHT);

    }

}

void Cell::run_timestep(){

    //.............Calculating the total length of both sides......................
    update_total_lengths();


    //.............Processing growth, shrinkage, (un)binding, nucleation.............
    for(int n = 0; n < N_MICROTUBULES; n++) {
        //ONE EVENT (catstrophe, rescue, bidning, unbinding) per timestep
        if (MiTus[n].get_state() == GROWING) {
            bool ev =  check_binding(n);
            MiTus[n].set_event(ev);
        }
    }
    for(int n = 0; n < N_MICROTUBULES; n++) {
        //growing, shrinking processes & catastrophe, rescue events.
        if (!MiTus[n].get_event()) {
            MiTus[n].process();
        }
    }



    for(int n = 0; n < N_MICROTUBULES; n++) {
        if (MiTus[n].get_state() == BOUND) {
            MiTus[n].check_host_length();
        }
    }
    for(int n = 0; n < N_MICROTUBULES; n++) {
        if(MiTus[n].get_min_length_t_step() < 0){
            double length_new_mt = (fabs(MiTus[n].get_min_length_t_step())/V_SHRINK + MiTus[n].get_t_event())*V_GROW;
            MiTus[n].reset(length_new_mt, dasl::mt_rng() < P_RIGHT);
        }
    }

}

bool Cell::check_binding(int n){
    double length = 0;
    if(MiTus[n].get_side() ==  RIGHT){
        length = l_left;  //length of opposing microtubules
    }else{
        length = l_right; //length of opposing microtubules
    }

    double p_bind;
    p_bind = 1 - exp(-T_STEP / halftime(length));

    if(dasl::mt_rng() < p_bind){
        double global_pos = dasl::mt_rng()*length;
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
        return true;
    }
    return false;
}

double Cell::halftime(double length){
    return 1/(BINDING_PER_LENGTH_PER_TIME*length);
}


double Cell::get_polarity() {
    return l_right/(l_left+l_right);
}

double Cell::polarity_numbers(){
    double n_right = 0.0;
    for(int n = 0; n < N_MICROTUBULES; n++){

        if(MiTus[n].get_side() == RIGHT){
            n_right += 1.0;
        }
    }
    return n_right/(double )N_MICROTUBULES;

}

double Cell::get_average_lenth(){
    return (l_left+l_right)/N_MICROTUBULES;
}

bool Cell::run_event() {

    //-----------------------Calculating Total Lengths------------------------------
    l_left  = 0;
    l_right = 0;
    int n_left[3] = {0, 0, 0}; //GROWING, SHRINKING, BOUND
    int n_right[3]= {0, 0, 0}; //GROWING, SHRINKING, BOUND
    for(int n = 0; n < N_MICROTUBULES; n++){
        if(MiTus[n].get_side() == RIGHT){
            l_right += MiTus[n].get_length();
            n_right[MiTus[n].get_state()] += 1;
        }else{
            l_left  += MiTus[n].get_length();
            n_left[MiTus[n].get_state()]  += 1;
        }
    }
    //std::cout << std::to_string(run_time)<<"   " <<std::to_string(l_left) <<"   " << std::to_string(l_right) <<"   " << std::to_string(n_right[GROWING])<<"   "  << std::to_string(n_right[SHRINKING])<<"   " << std::to_string(n_left[GROWING]) <<"   " << std::to_string(n_left[SHRINKING])<< "\n";

    //-----------------------Calculating AB for ABC-formula------------------------------
    double a[2];
    double b[2];
    a[LEFT] = 0.5*BINDING_PER_LENGTH_PER_TIME*(V_GROW*n_right[GROWING]-V_SHRINK*n_right[SHRINKING]);
    a[RIGHT]= 0.5*BINDING_PER_LENGTH_PER_TIME*(V_GROW*n_left[GROWING] -V_SHRINK*n_left[SHRINKING] );
    b[LEFT] =BINDING_PER_LENGTH_PER_TIME*l_right+R_CATASTROPHE;
    b[RIGHT]=BINDING_PER_LENGTH_PER_TIME*l_left +R_CATASTROPHE;

    //-----------------------Calculating times to event for every MT------------------------------
    double times[N_MICROTUBULES];
    for(int n = 0; n < N_MICROTUBULES; n++){
        int side = MiTus[n].get_side();
        times[n] = MiTus[n].calculated_time_to_event(a[side], b[side]);

    }
    //-----------------------Selecting smallest time to event------------------------------
    double smallest_time = run_time;
    int with_event = N_MICROTUBULES;
    for(int n = 0; n < N_MICROTUBULES; n++){
        if(times[n] < smallest_time){
            smallest_time = times[n];
            with_event = n;
        }
    }
    //-----------------------Running time until smallest time-------------------------------
    for(int n = 0; n < N_MICROTUBULES; n++){
        MiTus[n].run_time(smallest_time);
    }
    run_time -= smallest_time;
    //-----------------------Returning false when time has run out------------------------------
    if(with_event == N_MICROTUBULES){
        return false;
    }

    //-----------------------Applying event to MT with smallest event time----------------------
    double rbLt = 0.0;
    if(MiTus[with_event].get_state() == GROWING) {
        if (MiTus[with_event].get_side() == RIGHT) {
            rbLt = BINDING_PER_LENGTH_PER_TIME * (l_left + (V_GROW * n_left[GROWING] - V_SHRINK * n_left[SHRINKING]) * smallest_time);
        } else {
            rbLt = BINDING_PER_LENGTH_PER_TIME * (l_right + (V_GROW * n_right[GROWING] - V_SHRINK * n_right[SHRINKING]) * smallest_time);
        }
    }
    MiTus[with_event].execute_event(rbLt);

    //---------------If event is binding, the MT is given a host and binding position--------------
    if(MiTus[with_event].get_state() == BOUND) {
        double l_opposite = 0;
        for(int n = 0; n < N_MICROTUBULES; n++) {
            if (MiTus[n].get_side() != MiTus[with_event].get_side()) {
                l_opposite += MiTus[with_event].get_length();
            }
        }
        double global_pos = dasl::mt_rng()*l_opposite;
        bool searching = true;
        int s = 0;
        while(searching){
            if(MiTus[s].get_side() != MiTus[with_event].get_side()) {
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
        MiTus[with_event].bind_to_at_event(&MiTus[s] , global_pos);
    }

    //---------------Returning true to signal that we have not reached the end of time--------------
    return true;
}

void Cell::update_total_lengths(){
    l_left  = 0;
    l_right = 0;
    for(int n = 0; n < N_MICROTUBULES; n++){
        MiTus[n].set_event(false);
        if(MiTus[n].get_side() == RIGHT){
            l_right += MiTus[n].get_length();
        }else{
            l_left  += MiTus[n].get_length();
        }
    }

}
double Cell::get_runtime(){
    return run_time;
}