#include "utils.hpp"

int get_random_number(int max){
    return rand()%max;
}

std::vector<std::pair<int, int>> get_neighbors(int x, int y) {
    std::vector<std::pair<int, int>> res;
    if (x > 0) {
        res.push_back(std::make_pair(x - 1, y));
    }
    if (x < GRID_HEIGHT - 1) {
        res.push_back(std::make_pair(x + 1, y));
    }
    if (y > 0) {
        res.push_back(std::make_pair(x, y - 1));
    }
    if (y < GRID_WIDTH - 1) {
        res.push_back(std::make_pair(x, y + 1));
    }
    return res;
}
