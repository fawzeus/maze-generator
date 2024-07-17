#include "algorithms.hpp"

void dsf_maze(){
    Grid grid;
    grid.dfs_maze();
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"DFS Maze");
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.draw(window);
        window.display();
        window.clear();
    }
}
void dfs_maze_animation(){
    // Initialize random number generator 
    std::random_device rd; 
    std::mt19937 g(rd()); 
  
    Grid grid;
    std::stack<node> st;   
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    grid.get_cell(cell_x,cell_y).set_visited();
    std::vector <std::pair<int,int>>  neigbors = grid.get_neighbors(cell_x,cell_y);
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
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"DFS Maze Animation");
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
    }
}
void hunt_and_kill_maze(){
    Grid grid;
    grid.hunt_and_kill_maze();
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Hunt and Kill Maze");
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.draw(window);
        window.display();
        window.clear();
    }
}


void hunt_and_kill_maze_animation(){
   
    Grid grid;
    bool hunt = false,done = false;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    std::pair<int,int> current_cell=std::make_pair(cell_x,cell_y);
    std::pair<int,int> hunted_cell;
    grid.get_cell(cell_x,cell_y).set_visited();
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Hunt and Kill Maze Animation");
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(!done){
            if(!hunt){
                grid.set_highlited_cell(-1,-1);
                current_cell =  grid.hunt_and_kill_maze_animation(current_cell);
                if(current_cell.first==-1 and current_cell.second==-1){
                    hunt=true;
                    hunted_cell= std::make_pair(0,0);
                }
                sf::sleep(sf::milliseconds(10));
            }
            else {
                grid.set_highlited_cell(hunted_cell.first,hunted_cell.second);
                auto res = grid.hunt_animation(hunted_cell);
                if(res.second.second == true){
                    current_cell = std::make_pair(res.first,res.second.first);
                    hunt=false;
                }
                else if(res.first==-1 and res.second.first==-1){
                    hunt=false;
                    done=true;
                    grid.set_highlited_cell(-1,-1);
                }
                else{
                    hunted_cell = std::make_pair(res.first,res.second.first);
                }
                sf::sleep(sf::milliseconds(5));
            }
        }
        grid.draw(window);
        window.display();
        window.clear();
    }
}