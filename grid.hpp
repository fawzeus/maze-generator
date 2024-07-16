#include <stack>
#include <random> 
#include <algorithm>
#include "CONSTANTS.HPP"
#include "cell.hpp"
#include "utils.hpp"

class Grid {
    private:
        Cell cells[GRID_HEIGHT][GRID_WIDTH];
    public:
        Grid();
        void draw(sf::RenderWindow &window);
        void dfs_maze();
        void remove_wall(int x1, int y1, int x2, int y2);
        void dfs_maze_animation(std::stack<node> &st);
        Cell get_cell(int x,int y) const;
};