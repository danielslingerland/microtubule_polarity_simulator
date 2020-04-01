#include <iostream>

enum{GROW, SHRINK, BOUND, DEAD};
const double GROWSPEED = 1;
const double SHRINKSPEED = 5;

class Microtubule{
private:
    double length;
    int state;

public:

    Microtubule(){
        length = 0.0;
        state = GROW;

    }
    Microtubule(double l, int s){
        length = l;
        state = s;
    };
    void grow_shrink(){
        if(state == GROW){
            length += GROWSPEED;
        } else if (state == SHRINK){
            length -= SHRINKSPEED;
            if(length <= 0){
                state = DEAD;
            }
        }

    }

    void bind(bool binded){
        if(binded) {
            state = BOUND;
        }else {
            state = SHRINK;
        }
    }

    double get_length(){
        return length;
    }

    double get_state(){
        return state;
    }
};

int main() {
    std::cout << "microtubules is commited";
    return 0;
}

