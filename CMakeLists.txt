cmake_minimum_required(VERSION 3.15)
project(microtubule_polarity_simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(microtubule_polarity_simulator
        main.cpp Microtubule.cpp Microtubule.h Catch2_tests/testMicrotubule.cpp)
add_subdirectory(Catch2_tests)