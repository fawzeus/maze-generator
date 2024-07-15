#include "utils.hpp"

int get_random_number(int max){
    srand(time(0));
    return rand()%max;
}