#include "grid.hpp"

void Grid::draw(sf::RenderWindow &window){
    float pos_x=50,pos_y=50;
    for(int i=0;i<GRID_HEIGHT;i++){
        for(int j=0;j<GRID_WIDTH;j++){
            cells[i][j].draw(window,sf::Vector2f(pos_x+SQUARE_SIZE*i,pos_y+SQUARE_SIZE*j));
            //puts("hh");
        }
    }

}

void Grid::dfs_maze(){
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);

    Cell start_cell = cells[cell_x][cell_y];

}