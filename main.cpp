#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "CONSTANTS.HPP"

int main (){
    Grid grid;
    grid.dfs_maze();
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Maze");
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
    return 0;
}