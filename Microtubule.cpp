//
// Created by danie on 2-4-2020.
//

#include "Microtubule.h"
#include <random>
#include "RNG.h"

Microtubule::Microtubule(){
        length = dasl::distr(dasl::rng)*GROWSPEED;
        growing = true;
        bound = false;
        right_side = true;
    }

Microtubule::Microtubule(bool r){
    length = dasl::distr(dasl::rng)*GROWSPEED;
    growing = true;
    bound = false;
    right_side = r;
}
Microtubule::Microtubule(double l, bool g, bool b, bool r){
        length = l;
        growing = g;
        bound = b;
        right_side = r;
    };

void Microtubule::process(double t_step){
    min_length_t_step = length;
        if (!bound) {
            if (growing) {
                length += GROWSPEED*t_step;

                if(dasl::distr(dasl::rng) < P_CATASTROPHE){
                    double instant = dasl::distr(dasl::rng)*t_step;
                    length -= instant*GROWSPEED+(t_step-instant)*SHRINKSPEED;
                    growing = false;
                }
            } else {
                length -= SHRINKSPEED*t_step;
                if(dasl::distr(dasl::rng) < P_RESCUE){
                    double instant = dasl::distr(dasl::rng)*t_step;
                    length += instant*SHRINKSPEED+(t_step-instant)*GROWSPEED;
                    min_length_t_step = length-(t_step-instant)*GROWSPEED;
                    t_event = instant;
                    growing = true;
                }
            }
        }else{
            if(dasl::distr(dasl::rng) < P_UNBIND){
                bound = false;
            }


        }
}


void Microtubule::bind(Microtubule* host_mt, double pos){
        bound = true;
        growing = false;
        host = host_mt;
        bind_pos = pos;
        length -= dasl::distr(dasl::rng)*GROWSPEED;
}

void Microtubule::check_host_length(double t_step){
    if(host->get_min_length_t_step() < bind_pos){
        bound = false;
        if(host->is_growing()){
            length -= bind_pos - (host->get_min_length_t_step() - (t_step-host->get_t_event())*SHRINKSPEED); //What the length would have been without rescue
        }else {
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

bool Microtubule::is_growing(){
        return growing;
}
bool Microtubule::is_bound(){
        return bound;
}

bool Microtubule::is_right() {
    return right_side;
}
