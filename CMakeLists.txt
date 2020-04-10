cmake_minimum_required(VERSION 3.15)
project(microtubule_polarity_simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(microtubule_polarity_simulator
        main.cpp Microtubule.cpp Microtubule.h Cell.cpp Cell.h RNG.cpp RNG.h Parameters.h FileWriter.cpp FileWriter.h)
