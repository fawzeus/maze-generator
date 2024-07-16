#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstdlib> 
#include <time.h> 
#include "CONSTANTS.HPP"
#include <vector>
#include <utility>
#include "cell.hpp"

typedef struct node node;
int get_random_number(int max);
std::vector <std::pair<int,int>> get_neighbors(int x, int y);


struct node
{
    int prev_x,prev_y,current_x,current_y;
    node& operator =(const node& a){
        prev_x=a.prev_x;
        prev_y=a.prev_y;
        current_x=a.current_x;
        current_y=a.current_y;
        return *this;
    }
};



#endif

