#include <SFML/Graphics.hpp>
#include "CONSTANTS.HPP"

int main (){
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Maze");
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
        window.clear();
    }
    return 0;
}