//
// Created by danie on 8-4-2020.
//

#include "FileWriter.h"
#include <ctime>
using namespace std;

FileWriter::FileWriter(string fname) {
    string final_name = fname+".txt";
    ifstream infile("../DATA/"+final_name);
    bool exists = infile.good();
    int count = 1;
    while(exists){
        count += 1;
        final_name = fname + to_string(count)+".txt";
        ifstream infile2("../DATA/"+final_name);
        exists = infile2.good();

    }

    filename = "../DATA1/"+final_name;
}

void FileWriter::writeParameters(double BINDING_PER_LENGTH_PER_TIME){
    time_t now = time(0);
    char* dt = ctime(&now);
    ofstream myfile;
    myfile.open(filename, ios::app);
    myfile << "simulation started writing at: " << dt;
    myfile << "T_STEP: " << T_STEP << "\n";
    myfile << "N_MICROTUBULES: " << N_MICROTUBULES << "\n";
    myfile << "R_CATASTROPHE: " << R_CATASTROPHE << "\n";
    myfile << "R_RESCUE: " << R_RESCUE << "\n";
    myfile << "R_UNBIND: " << R_UNBIND << "\n";
    myfile << "V_GROW: " << V_GROW << "\n";
    myfile << "V_SHRINK: " << V_SHRINK << "\n";
    myfile << "BINDING_PER_LENGTH_PER_TIME: " << BINDING_PER_LENGTH_PER_TIME << "\n";
    myfile << "P_RIGHT: " << P_RIGHT << "\n";
    myfile << "HOST_PENALTY_FACTOR: " << HOST_PENALTY_FACTOR << "\n";
    myfile << "DATA\n";
    myfile.close();
}


void FileWriter::writeString(std::string note) {
    ofstream myfile;
    myfile.open(filename, ios::app);
    myfile << note <<"\n";
    myfile.close();

}

void FileWriter::writeDouble(double data) {
    ofstream myfile;
    myfile.open(filename, ios::app);
    myfile << data<<"\n";
    myfile.close();

}

void FileWriter::writeDoubleArray(double data[], int n_data){
    ofstream myfile;
    myfile.open(filename, ios::app);
    for(int n = 0; n < n_data; n++){
        myfile << data[n]<<"\n";
    }
    myfile.close();

}

void FileWriter::writeIntArray(int data[], int n_data){
    ofstream myfile;
    myfile.open(filename, ios::app);
    for(int n = 0; n < n_data; n++){
        myfile << data[n]<<"\n";
    }
    myfile.close();

}
