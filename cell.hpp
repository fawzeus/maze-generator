#ifndef CELL_HPP
#define CELL_HPP
#include "CONSTANTS.HPP"

class Cell{
    private:
        bool left,right,top,bottom;
        const static short TOP=0,LEFT=1,RIGHT=2,BOTTOM=3;
        bool is_visited;
    public:
        Cell();
        Cell(const Cell &other); 
        Cell& operator=(const Cell &other);
        void clear_wall(const short  side);
        void draw(sf::RenderWindow &window, sf::Vector2f position);
        bool check_if_visited();
        bool set_visited();
};

#endif