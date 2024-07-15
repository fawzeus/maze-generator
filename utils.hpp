#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstdlib> 
#include <time.h> 
#include "CONSTANTS.HPP"
#include "grid.hpp"
#include <vector>
int get_random_number(int max);
std::vector <Cell> get_neighbors(Cell cell);

#endif