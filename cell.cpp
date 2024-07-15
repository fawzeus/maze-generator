#include "cell.hpp"


Cell::Cell() : left(true), right(true), top(true), bottom(true), is_visited(false) {}

Cell::Cell(const Cell &other) : left(other.left), right(other.right), top(other.top), bottom(other.bottom), is_visited(other.is_visited) {}

Cell& Cell::operator=(const Cell &other) {
    if (this != &other) { // Check for self-assignment
        left = other.left;
        right = other.right;
        top = other.top;
        bottom = other.bottom;
        is_visited = other.is_visited;
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

void Cell::draw(sf::RenderWindow &window, sf::Vector2f position) {
    // Draw top wall
    if (top) {
        sf::RectangleShape topWall(sf::Vector2f(SQUARE_SIZE, LINE_THICKNESS));
        topWall.setPosition(position);
        topWall.setFillColor(sf::Color::White);
        window.draw(topWall);
    }

    // Draw left wall
    if (left) {
        sf::RectangleShape leftWall(sf::Vector2f(LINE_THICKNESS, SQUARE_SIZE));
        leftWall.setPosition(position);
        leftWall.setFillColor(sf::Color::White);
        window.draw(leftWall);
    }

    // Draw right wall
    if (right) {
        sf::RectangleShape rightWall(sf::Vector2f(LINE_THICKNESS, SQUARE_SIZE));
        rightWall.setPosition(position + sf::Vector2f(SQUARE_SIZE - LINE_THICKNESS, 0));
        rightWall.setFillColor(sf::Color::White);
        window.draw(rightWall);
    }

    // Draw bottom wall
    if (bottom) {
        sf::RectangleShape bottomWall(sf::Vector2f(SQUARE_SIZE, LINE_THICKNESS));
        bottomWall.setPosition(position + sf::Vector2f(0, SQUARE_SIZE - LINE_THICKNESS));
        bottomWall.setFillColor(sf::Color::White);
        window.draw(bottomWall);
    }
}

bool Cell::check_if_visited(){
    return is_visited;
}


bool Cell::set_visited(){
    is_visited=true;
}