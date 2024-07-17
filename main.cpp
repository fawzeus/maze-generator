#include "algorithms.hpp"

int main() {
start:
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mazes Algorithms");

    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        return -1;  // Handle error
    }

    sf::Text instructionText, welcome_text,list;
    instructionText.setFont(font); welcome_text.setFont(font);list.setFont(font);
    instructionText.setString("1. Hunt and Kill Maze Animation\n"
                              "2. Hunt and Kill Maze\n"
                              "3. DFS Maze\n"
                              "4. DFS Maze Animation\n"
                              "5. Prim's Maze\n"
                              "6. Prim's Maze Animation\n"
                              "Q. Quit");
    welcome_text.setString("Welcome to the Maze Generator");
    list.setString("Press the following buttons to select an algorithm:");
    instructionText.setCharacterSize(25);welcome_text.setCharacterSize(40);list.setCharacterSize(30);
    instructionText.setOrigin(instructionText.getGlobalBounds().width/2,instructionText.getGlobalBounds().height/2);
    instructionText.setPosition(WIDTH/2+50, HEIGHT/2);
    welcome_text.setOrigin(welcome_text.getGlobalBounds().width/2,welcome_text.getGlobalBounds().height/2);
    list.setOrigin(list.getGlobalBounds().width/2,list.getGlobalBounds().height/2);
    welcome_text.setPosition(WIDTH/2,50);
    list.setPosition(WIDTH/2,400);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1) {
                    window.close();
                    hunt_and_kill_maze_animation();
                    goto start;
                } else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2) {
                    window.close();
                    hunt_and_kill_maze();
                    goto start;
                } else if (event.key.code == sf::Keyboard::Numpad3 || event.key.code == sf::Keyboard::Num3) {
                    window.close();
                    dsf_maze();
                    goto start;
                } else if (event.key.code == sf::Keyboard::Numpad4 || event.key.code == sf::Keyboard::Num4) {
                    window.close();
                    dfs_maze_animation();
                    goto start;
                } else if (event.key.code == sf::Keyboard::Numpad5 || event.key.code == sf::Keyboard::Num5) {
                    window.close();
                    prim_maze();
                    goto start;
                } else if (event.key.code == sf::Keyboard::Numpad6 || event.key.code == sf::Keyboard::Num6) {
                    window.close();
                    prim_maze_animation();
                    goto start;
                }
                else if(event.key.code == sf::Keyboard::Q){
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(instructionText);
        window.draw(list);
        window.draw(welcome_text);
        window.display();
    }

    return 0;
}
