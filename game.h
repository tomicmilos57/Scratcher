#ifndef Game_Scratcher
#define Game_Scratcher
#include "stroke.h"
#include "shape.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <set>
#include <stack>
class Game {
    private:
        sf::RenderWindow &window;
        //std::set<Point> set;
        std::vector<Stroke*>arr;
        std::stack<Stroke*>stack_undo;
        int width;
        int height;
        Shape_Rect rect;
        Shape_Dot dot;
        Shape_Circle circle;
        Shape *shape = &dot;
        int color = 0;
        static sf::Color colors[];
    public:
        Game(sf::RenderWindow &window, int w, int h)
            : window(window), width(w), height(h), rect(this), dot(this), circle(this) {}
        void event();
        void draw() const;
    private:
        void saveGame() const;
        void loadGame();
        void incColor() { color < 6 ? color += 1 : color = 0; }
        void decColor() { color > 0 ? color -= 1 : color = 6; }
        void insert_pixel(Stroke*,Point);
        void fill_line(Stroke*, int, int, int, int);
        void clear_stack();
        friend Shape_Rect;
        friend Shape_Dot;
        friend Shape_Circle;
};

#endif
