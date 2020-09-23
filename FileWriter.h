//
// Created by danie on 8-4-2020.
//

#ifndef MICROTUBULE_POLARITY_SIMULATOR_FILEWRITER_H
#define MICROTUBULE_POLARITY_SIMULATOR_FILEWRITER_H
#include<string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Microtubule.h"

class FileWriter {
private:
    std::string filename;
public:
    FileWriter(std::string fname);
    void writeParameters(double BINDING_PER_LENGTH_PER_TIME, double P_RIGHT);
    void writeString(std::string note);
    void writeDouble(double data);
    void writeDoubleArray(double data[], int n_data);
    void writeIntArray(int data[], int n_data);

};


#endif //MICROTUBULE_POLARITY_SIMULATOR_FILEWRITER_H
