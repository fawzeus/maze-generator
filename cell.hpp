#ifndef CELL_HPP
#define CELL_HPP
#include "CONSTANTS.HPP"

class Cell{
    private:
        bool left,right,top,bottom;
        const static short TOP=0,LEFT=1,RIGHT=2,BOTTOM=3;
        bool is_visited;
        std::pair<int,int> direction;
    public:
        Cell();
        Cell(const Cell &other); 
        Cell& operator=(const Cell &other);
        void clear_wall(const short  side);
        void draw(sf::RenderWindow &window, sf::Vector2f position, bool highlited = false);
        bool check_if_visited () const;
        void set_visited();
        void remove_top_wall() { top = false; }
        void remove_bottom_wall() { bottom = false; }
        void remove_left_wall() { left = false; }
        void remove_right_wall() { right = false; }
        void add_top_wall() { top = true; }
        void add_bottom_wall() { bottom = true; }
        void add_left_wall() { left = true; }
        void add_right_wall() { right = true; }
        bool has_top_wall() const { return top; }
        bool has_bottom_wall() const { return bottom; }
        bool has_left_wall() const { return left; }
        bool has_right_wall() const { return right; }
        void vist_not(){puts( is_visited ?"visited":"not visited");}
        void set_direction(int x, int y);
        std::pair<int,int> get_direction();
};

#endif