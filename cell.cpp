#include "cell.hpp"


Cell::Cell() : left(true), right(true), top(true), bottom(true), is_visited(false) {
    direction = std::make_pair(-1,-1);
}

Cell::Cell(const Cell &other) : left(other.left), right(other.right), top(other.top), bottom(other.bottom), is_visited(other.is_visited) , direction(other.direction){
}

Cell& Cell::operator=(const Cell &other) {
    if (this != &other) { // Check for self-assignment
        left = other.left;
        right = other.right;
        top = other.top;
        bottom = other.bottom;
        is_visited = other.is_visited;
        direction = other.direction;
    }
    return *this;
}

void Cell::clear_wall(const short side){
    switch (side)
    {
    case Cell::TOP:
        top=false;
        break;
    case Cell::LEFT:
        left=false;
        break;
    case Cell::BOTTOM:
        bottom=false;
        break;
    case Cell::RIGHT:
        right=false;
        break;
    default:
        puts("INVALID ENTRY !!");
        break;
    }
}

void Cell::draw(sf::RenderWindow &window, sf::Vector2f position, bool highlited) {
    sf::Color color= sf::Color::White;
    if(highlited){
        sf::RectangleShape highlight(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
        highlight.setPosition(position);
        highlight.setFillColor(sf::Color::Red);
        window.draw(highlight);
        return;
    }
    // Draw top wall
    if (top or highlited) {
        sf::RectangleShape topWall(sf::Vector2f(SQUARE_SIZE, LINE_THICKNESS));
        topWall.setPosition(position);
        topWall.setFillColor(color);
        window.draw(topWall);
    }

    // Draw left wall
    if (left or highlited) {
        sf::RectangleShape leftWall(sf::Vector2f(LINE_THICKNESS, SQUARE_SIZE));
        leftWall.setPosition(position);
        leftWall.setFillColor(color);
        window.draw(leftWall);
    }

    // Draw right wall
    if (right or highlited) {
        sf::RectangleShape rightWall(sf::Vector2f(LINE_THICKNESS, SQUARE_SIZE));
        rightWall.setPosition(position + sf::Vector2f(SQUARE_SIZE - LINE_THICKNESS, 0));
        rightWall.setFillColor(color);
        window.draw(rightWall);
    }

    // Draw bottom wall
    if (bottom or highlited) {
        sf::RectangleShape bottomWall(sf::Vector2f(SQUARE_SIZE, LINE_THICKNESS));
        bottomWall.setPosition(position + sf::Vector2f(0, SQUARE_SIZE - LINE_THICKNESS));
        bottomWall.setFillColor(color);
        window.draw(bottomWall);
    }
}

bool Cell::check_if_visited ()const{
    return is_visited;
}


void Cell::set_visited(){
    is_visited=true;
}


void Cell::set_direction(int x, int y){
    direction=std::make_pair(x,y);
}

std::pair<int,int> Cell::get_direction(){
    return direction;
}