#include <iostream>
#include <cstdlib>
#include "Microtubule.h"


int main() {
    //srand(1);
    Microtubule first_mt = Microtubule();
    std::cout << "microtubules length: " << std::to_string(first_mt.get_length());
    for(int i = 0; i < 100; i++) {
        first_mt.process();
        std::cout << "\nmicrotubules length: " << std::to_string(first_mt.get_length());
    }
    //Microtubule second_mt = Microtubule();
    return 0;
}

