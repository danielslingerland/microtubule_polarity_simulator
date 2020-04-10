//
// Created by danie on 2-4-2020.
//

#include "Microtubule.h"
#include "RNG.h"

//constructor used by Cell.h to create an empty MiTus array.
Microtubule::Microtubule(){
    length = dasl::mt_rng() * V_GROW;
    side = RIGHT;
    state = GROWING;
}

//constructor used at initiation of Cell, side is randomly decided by cell.
Microtubule::Microtubule(bool r){
    length = dasl::mt_rng() * V_GROW;
    side = r;
    state = GROWING;
}

//constructor used during simulation to reset microtubule if length < 0.
// Could be replaced by a reset function if deemed better in the future.
Microtubule::Microtubule(double l, bool r){
    length = l;
    side = r;
    state = GROWING;
};

//public function process is executed at the start of every timestep.
//processes independend of other microtubules are placed here, processes dependend on other MTs are placed in the Cell
void Microtubule::process(){
    min_length_t_step = length;
    t_event = 0;
    if (state == GROWING) {
        length += V_GROW * T_STEP;

        if(dasl::mt_rng() < P_CATASTROPHE){
            double instant = dasl::mt_rng() * T_STEP;
            length -= instant * V_GROW + (T_STEP - instant) * V_SHRINK;
            state = SHRINKING;
        }
    } else if(state == SHRINKING) {
        length -= V_SHRINK * T_STEP;
        if(dasl::mt_rng() < P_RESCUE){
            t_event = dasl::mt_rng() * T_STEP;
            length += t_event * V_SHRINK + (T_STEP - t_event) * V_GROW;
            min_length_t_step = length- (T_STEP - t_event) * V_GROW;
            state = GROWING;
        }else {
            min_length_t_step = length;
        }
    }else if(state == BOUND){
            if(dasl::mt_rng() < P_UNBIND){
                state = SHRINKING;
            }
    }


}

//public function to bind this microtubule to the given MT at position.
void Microtubule::bind_to_at(Microtubule* host_mt, double pos){
        state = BOUND;
        host = host_mt;
        bind_pos = pos;
        length -= dasl::mt_rng() * V_GROW;
}

void Microtubule::check_host_length(){
    if(host->get_min_length_t_step() < bind_pos){
        state = SHRINKING;
        if(host->get_state() == GROWING){
            length -= bind_pos - (host->get_min_length_t_step() - (T_STEP-host->get_t_event()) * V_SHRINK); //What the length would have been without rescue
        }else if(host->get_state() == SHRINKING){
            length -= bind_pos - host->get_length();
        }
    }

}



double Microtubule::get_length(){
        return length;
}

double Microtubule::get_min_length_t_step() {
    return min_length_t_step;
}

double Microtubule::get_t_event(){
    return t_event;
}

int Microtubule::get_state(){
    return state;
}

bool Microtubule::get_side(){
    return side;
}


