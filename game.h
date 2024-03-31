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
        //enum Status{
        //    dot,rectangle
        //};
        //Status status = dot; //Option of drawing
        //sf::RectangleShape* rect_overlay; //Overlay for rectangle
        //bool overlay_draw = true; // if in overlay mode and Lclick is released, dont draw overaly
        Shape_Rect rect;
        Shape_Dot dot;
        Shape *shape = &dot;
        int radius = 1;
        int color = 0;
        static sf::Color colors[];
    public:
        Game(sf::RenderWindow &window, int w, int h)
            : window(window), width(w), height(h), rect(this), dot(this) {}
        void event();
        void draw() const;
    private:
        void saveGame() const;
        void loadGame();
        void incRadius() { radius < 20 ? radius += 1 : 20; } 
        void decRadius() { radius > 1 ? radius -= 1 : 1; }
        void incColor() { color < 6 ? color += 1 : color = 0; }
        void decColor() { color > 0 ? color -= 1 : color = 6; }
        void insert_pixel(Stroke*,Point);
        void fill_line(Stroke*, int, int, int, int);
        void clear_stack();
        void insert_rect();
        friend Shape_Rect;
        friend Shape_Dot;
};

#endif
