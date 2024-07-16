#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "CONSTANTS.HPP"

int main (){
    // Initialize random number generator 
    std::random_device rd; 
    std::mt19937 g(rd()); 
  
    Grid grid;
    //grid.dfs_maze();
    std::stack<node> st;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    grid.get_cell(cell_x,cell_y).set_visited();
    std::vector <std::pair<int,int>>  neigbors = get_neighbors(cell_x,cell_y);
    // Shuffle the vector 
    std::shuffle(neigbors.begin(), neigbors.end(), g);
    for ( auto pos:neigbors){
            if(!grid.get_cell(pos.first,pos.second).check_if_visited()){
                grid.get_cell(pos.first,pos.second).set_visited();
                node nd;
                nd.current_x = pos.first;
                nd.current_y = pos.second;
                nd.prev_x = cell_x;
                nd.prev_y = cell_y;
                st.push(nd);
            }
        }
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Maze");
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.dfs_maze_animation(st);
        grid.draw(window);
        window.display();
        window.clear();
        sf::sleep(sf::milliseconds(50));
    }
    return 0;
}