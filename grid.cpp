#include "grid.hpp"


Grid::Grid() {
    srand(time(0));
    highlited_cell = std::make_pair(-1,-1);
}

void Grid::set_highlited_cell(int x,int y){
    highlited_cell = std::make_pair(y,x);
}
void Grid::draw(sf::RenderWindow &window){
    float pos_x=WIDTH/2-GRID_WIDTH*SQUARE_SIZE/2,pos_y=HEIGHT/2-GRID_HEIGHT*SQUARE_SIZE/2-50;
    for(int i=0;i<GRID_HEIGHT;i++){
        for(int j=0;j<GRID_WIDTH;j++){
            if(i==highlited_cell.first and j==highlited_cell.second) cells[i][j].draw(window,sf::Vector2f(pos_x+SQUARE_SIZE*i,pos_y+SQUARE_SIZE*j),true);
            else cells[i][j].draw(window,sf::Vector2f(pos_x+SQUARE_SIZE*i,pos_y+SQUARE_SIZE*j));
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

void Grid::dfs_maze_animation(std::stack<node> &st){
    if(st.empty()) return;
    std::random_device rd; 
    std::mt19937 g(rd());
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

Cell Grid::get_cell(int x,int y)const {
    return cells[x][y];
}

void Grid::set_cell_as_visited(int x,int y){
    cells[x][y].set_visited();
}

std::pair<int,int> Grid::hunt() const{
    for(int i=0;i<GRID_HEIGHT;i++){
        for(int j=0;j<GRID_WIDTH;j++){
            if (!cells[i][j].check_if_visited()){
                std::vector <std::pair<int,int>>  neigbors = get_neighbors(i,j,true);
                for(auto neigbor:neigbors){
                    if(cells[neigbor.first][neigbor.second].check_if_visited()){
                        return neigbor;
                    }
                }
            }
        }
    }
    return std::make_pair(-1,-1);
}

void Grid::hunt_and_kill_maze(){
    bool hunted = true;
    bool dead_end = false;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    std::pair<int,int> current_cell=std::make_pair(cell_x,cell_y);
    cells[cell_x][cell_y].set_visited();
    std::vector <std::pair<int,int>>  neigbors = get_neighbors(cell_x,cell_y);
    std::pair<int,int> next_cell = neigbors[get_random_number(neigbors.size())];
    while(hunted){
        while(!dead_end){
            std::vector <std::pair<int,int>>  neigbors = get_neighbors(next_cell.first,next_cell.second);
            cells[next_cell.first][next_cell.second].set_visited();
            remove_wall(next_cell.first,next_cell.second,current_cell.first,current_cell.second);
            current_cell = next_cell;
            if(neigbors.size()!=0)
                next_cell = neigbors[get_random_number(neigbors.size())];
                
            else
                dead_end=true;
        }
        next_cell = hunt();
        if(next_cell.first==-1 and next_cell.second==-1){
            hunted=false;
            break;
        }
        dead_end=false;

    }
}

std::vector<std::pair<int, int>> Grid::get_neighbors(int x, int y, bool  visited) const {
    std::vector<std::pair<int, int>> res;
    if(visited){
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
    }
    else {
        if (x > 0 and !get_cell(x-1,y).check_if_visited()) {
            res.push_back(std::make_pair(x - 1, y));
        }
        if (x < GRID_HEIGHT - 1 and !get_cell(x+1,y).check_if_visited()) {
            res.push_back(std::make_pair(x + 1, y));
        }
        if (y > 0 and !get_cell(x,y-1).check_if_visited()) {
            res.push_back(std::make_pair(x, y - 1));
        }
        if (y < GRID_WIDTH - 1 and !get_cell(x,y+1).check_if_visited()) {
            res.push_back(std::make_pair(x, y + 1));
        }
    }
    return res;
}


std::pair<int,int> Grid::hunt_and_kill_maze_animation(std::pair<int,int> current_cell){
    std::vector <std::pair<int,int>>  neigbors = get_neighbors(current_cell.first,current_cell.second);
    if (neigbors.size()==0) return std::make_pair(-1,-1);
    std::pair<int,int> next_cell = neigbors[get_random_number(neigbors.size())];
    remove_wall(next_cell.first,next_cell.second,current_cell.first,current_cell.second);
    cells[next_cell.first][next_cell.second].set_visited();
    return next_cell;

}
std::pair<int,std::pair<int,bool>> Grid::hunt_animation(std::pair<int,int> current_cell){
    if (!cells[current_cell.first][current_cell.second].check_if_visited()){
        std::vector <std::pair<int,int>>  neigbors = get_neighbors(current_cell.first,current_cell.second,true);
        for(auto neigbor:neigbors){
            if(cells[neigbor.first][neigbor.second].check_if_visited()){
                return std::make_pair(neigbor.first,std::make_pair(neigbor.second,true));
            }
        }
    }
    if (current_cell.second < GRID_WIDTH - 1 ){
        return std::make_pair(current_cell.first,std::make_pair(current_cell.second+1,false));
    }
    else if(current_cell.first< GRID_HEIGHT - 1){
        return std::make_pair(current_cell.first+1,std::make_pair(0,false));
    }
    else {
        return std::make_pair(-1,std::make_pair(-1,false));
    }
        
}

void Grid::prim_maze() {
    std::random_device rd;
    std::mt19937 g(rd());

    // Step 1: Start with a random cell
    int start_x = get_random_number(GRID_HEIGHT);
    int start_y = get_random_number(GRID_WIDTH);
    cells[start_x][start_y].set_visited();

    // Step 2: Add the walls of the cell to the list of walls
    std::vector<std::tuple<int, int, int, int>> walls;
    if (start_x > 0) walls.push_back(std::make_tuple(start_x, start_y, start_x - 1, start_y));
    if (start_x < GRID_HEIGHT - 1) walls.push_back(std::make_tuple(start_x, start_y, start_x + 1, start_y));
    if (start_y > 0) walls.push_back(std::make_tuple(start_x, start_y, start_x, start_y - 1));
    if (start_y < GRID_WIDTH - 1) walls.push_back(std::make_tuple(start_x, start_y, start_x, start_y + 1));

    // Step 3: Loop until there are no walls left in the list
    while (!walls.empty()) {
        // Step 4: Randomly select a wall from the list
        std::shuffle(walls.begin(), walls.end(), g);
        auto wall = walls.back();
        walls.pop_back();

        int x1 = std::get<0>(wall);
        int y1 = std::get<1>(wall);
        int x2 = std::get<2>(wall);
        int y2 = std::get<3>(wall);

        // Step 5: If only one of the two cells divided by the wall is visited
        if (cells[x2][y2].check_if_visited() != cells[x1][y1].check_if_visited()) {
            // Remove the wall between the two cells
            remove_wall(x1, y1, x2, y2);

            // Mark the unvisited cell as part of the maze
            cells[x2][y2].set_visited();

            // Add the neighboring walls of the cell to the list
            if (x2 > 0 && !cells[x2 - 1][y2].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2 - 1, y2));
            if (x2 < GRID_HEIGHT - 1 && !cells[x2 + 1][y2].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2 + 1, y2));
            if (y2 > 0 && !cells[x2][y2 - 1].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2, y2 - 1));
            if (y2 < GRID_WIDTH - 1 && !cells[x2][y2 + 1].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2, y2 + 1));
        }
    }
}

bool Grid::prim_maze_animation_step(std::vector<std::tuple<int, int, int, int>>& walls) {
    if (walls.empty()) return false;
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(walls.begin(), walls.end(), g);
    
    auto wall = walls.back();
    walls.pop_back();
    
    int x1 = std::get<0>(wall);
    int y1 = std::get<1>(wall);
    int x2 = std::get<2>(wall);
    int y2 = std::get<3>(wall);
    
    if (cells[x2][y2].check_if_visited() != cells[x1][y1].check_if_visited()) {
        remove_wall(x1, y1, x2, y2);
        cells[x2][y2].set_visited();
        
        if (x2 > 0 && !cells[x2 - 1][y2].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2 - 1, y2));
        if (x2 < GRID_HEIGHT - 1 && !cells[x2 + 1][y2].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2 + 1, y2));
        if (y2 > 0 && !cells[x2][y2 - 1].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2, y2 - 1));
        if (y2 < GRID_WIDTH - 1 && !cells[x2][y2 + 1].check_if_visited()) walls.push_back(std::make_tuple(x2, y2, x2, y2 + 1));
        
        return true;
    }
    
    return true;
}