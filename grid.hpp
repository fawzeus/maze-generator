#include "CONSTANTS.HPP"
#include "cell.hpp"
#include "utils.hpp"
class Grid {
    private:
        Cell cells[GRID_HEIGHT][GRID_WIDTH];
    public:
        Grid(){};
        void draw(sf::RenderWindow &window);
        void dfs_maze();
};