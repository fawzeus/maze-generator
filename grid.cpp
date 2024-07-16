#include "grid.hpp"


Grid::Grid() {
    srand(time(0));
}
void Grid::draw(sf::RenderWindow &window){
    float pos_x=50,pos_y=50;
    for(int i=0;i<GRID_HEIGHT;i++){
        for(int j=0;j<GRID_WIDTH;j++){
            cells[i][j].draw(window,sf::Vector2f(pos_x+SQUARE_SIZE*i,pos_y+SQUARE_SIZE*j));
        }
    }

}


void Grid::remove_wall(int x1, int y1, int x2, int y2) {
    if (x1 == x2 and y1 == y2 + 1) { // c1 is to the right of c2
        cells[y1][x1].remove_left_wall();
        cells[y2][x2].remove_right_wall();
    }
    else if (x1 == x2 and y1 == y2 - 1) { // c1 is to the left of c2
        cells[y1][x1].remove_right_wall();
        cells[y2][x2].remove_left_wall();
    }
    else if (x1 == x2 + 1 and y1 == y2) { // c1 is below c2
        cells[y1][x1].remove_top_wall();
        cells[y2][x2].remove_bottom_wall();
    }
    else if (x1 == x2 - 1 and y1 == y2) { // c1 is above c2
        cells[y1][x1].remove_bottom_wall();
        cells[y2][x2].remove_top_wall();
    }
}

void Grid::dfs_maze(){
    // Initialize random number generator 
    std::random_device rd; 
    std::mt19937 g(rd()); 
  
 
    std::stack<node> st;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    cells[cell_x][cell_y].set_visited();
    std::vector <std::pair<int,int>>  neigbors = get_neighbors(cell_x,cell_y);
    // Shuffle the vector 
    std::shuffle(neigbors.begin(), neigbors.end(), g);
    for ( auto pos:neigbors){
            if(!cells[pos.first][pos.second].check_if_visited()){
                cells[pos.first][pos.second].set_visited();
                node nd;
                nd.current_x = pos.first;
                nd.current_y = pos.second;
                nd.prev_x = cell_x;
                nd.prev_y = cell_y;
                st.push(nd);
            }
        }
    
    while (!st.empty()){
        node current_node = st.top();st.pop();
        remove_wall(current_node.current_x,current_node.current_y,current_node.prev_x,current_node.prev_y);
        std::vector <std::pair<int,int>>  neigbors = get_neighbors(current_node.current_x,current_node.current_y);
        // Shuffle the vector 
        std::shuffle(neigbors.begin(), neigbors.end(), g);
        for ( auto pos:neigbors){
            if(!cells[pos.first][pos.second].check_if_visited()){
                cells[pos.first][pos.second].set_visited();
                node nd;
                nd.current_x = pos.first;
                nd.current_y = pos.second;
                nd.prev_x = current_node.current_x;
                nd.prev_y = current_node.current_y;
                st.push(nd);
            }
        }
    }

    
}