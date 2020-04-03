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
    length = 0.0;
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
        if (!bound) {
            if (growing) {
                length += GROWSPEED*t_step;

                if(dasl::distr(dasl::rng) < P_CATASTROPHE){
                    double instant = dasl::distr(dasl::rng)*t_step;
                    length -= instant*GROWSPEED+(t_step-instant)*SHRINKSPEED
                    growing = false;
                }
            } else {
                length -= SHRINKSPEED*t_step;
                if(dasl::distr(dasl::rng) < P_RESCUE){
                    double instant = dasl::distr(dasl::rng)*t_step;
                    length += instant*SHRINKSPEED+(t_step-instant)*GROWSPEED
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

void Microtubule::check_host_length(){
    if(host->get_length() < bind_pos){
        bound = false;
        length -= bind_pos-host->get_length();
    }

}

double Microtubule::get_length(){
        return length;
}

bool Microtubule::is_growing(){
        return growing;
}
bool Microtubule::is_bound(){
        return bound;
}
