//
// Created by danie on 2-4-2020.
//

#include "Microtubule.h"
#include <stdlib.h>

Microtubule::Microtubule(){
        length = 0.0;
        growing = true;
        bound = false;

    }
Microtubule::Microtubule(double l, bool g, bool b){
        length = l;
        growing = g;
        bound = b;
    };
void Microtubule::grow_shrink(){
        if (!bound) {
            if (growing) {
                length += GROWSPEED;

                if(rand()/RAND_MAX < P_CATASTROPHE){
                    growing = false
                }
            } else {
                length -= SHRINKSPEED;
                if(rand()/RAND_MAX < P_RESCUE){
                    growing = true
                }
            }
        }else{
            if(rand()/RAND_MAX < P_UNBIND){
                bound = false;
            }

        }
}

void Microtubule::bind(Microtubule* host_mt, double pos){
        bound = true;
        growing = false;
        host = host_mt;
        bind_pos = pos;
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
