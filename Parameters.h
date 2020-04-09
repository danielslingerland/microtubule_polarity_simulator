//
// Created by danie on 7-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_PARAMETERS_H
#define MICROTUBULE_POLARITY_SIMULATOR_PARAMETERS_H

#endif //MICROTUBULE_POLARITY_SIMULATOR_PARAMETERS_H

//Values from Xavi Fernandez-Luengo Flores MSc Thesis (Table 4.11)
//T : seconds (s)
#define T_STEP 1
#define N_MICROTUBULES 1000
//R : per second (s^-1)
#define R_CATASTROPHE 0.025
#define R_RESCUE 0.038
#define R_UNBIND 0.1
//V : micrometer per second (um/s)
#define V_GROW 0.093
#define V_SHRINK 0.39
//P: probability
#define P_RIGHT 0.5

const double P_CATASTROPHE = R_CATASTROPHE*T_STEP;
const double P_RESCUE = R_RESCUE*T_STEP;
const double P_UNBIND = R_UNBIND*T_STEP;
enum{GROWING, SHRINKING, BOUND};
enum{RIGHT, LEFT};
