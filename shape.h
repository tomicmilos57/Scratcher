#ifndef shape_h
#define shape_h
//#include "point.h"
#include <SFML/Graphics/RectangleShape.hpp> 
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
class Point;
class Game;
class Stroke;
class Shape{ //Abstract class 
    protected:
        Game* game;
        Shape(Game* g) : game(g){}
    public:
        virtual void onClick(Point& prev, Point& p, bool &newstroke){}
        virtual void drawOverlay(bool) const{}
        virtual void insert(){}
};
class Shape_Dot : public Shape{
    public:
        Shape_Dot(Game* g) : Shape(g) {}
        void onClick(Point& prev, Point& p, bool &newstroke);
        void drawOverlay(bool) const;
        void insert();
};

class Shape_Rect : public Shape{
    private:
        sf::RectangleShape* rect_overlay;
    public:
        Shape_Rect(Game* g) : Shape(g) {
            rect_overlay = new sf::RectangleShape();
            rect_overlay->setFillColor(sf::Color(0,0,0,0));
            rect_overlay->setOutlineThickness(1);
        }
        void onClick(Point& prev, Point& p, bool &newstroke);
        void drawOverlay(bool) const;
        void insert();
        //Destructor
};
class Shape_Circle : public Shape{
    private:
        sf::CircleShape* circle_overlay;
        void drawCircle(Stroke*,int x, int y, int r);
        void drawEightPoints(Stroke*, int xc, int yc, int x, int y);
    public:
        Shape_Circle(Game* g) : Shape(g) {
            circle_overlay = new sf::CircleShape();
            circle_overlay->setFillColor(sf::Color(0,0,0,0));
            circle_overlay->setOutlineThickness(1);
        }
        void onClick(Point& prev, Point& p, bool &newstroke);
        void drawOverlay(bool) const;
        void insert();
};
class Shape_Line : public Shape{
    private:
        sf::Vertex line_overlay[2];
    public:
        Shape_Line(Game* g) : Shape(g) {
            /*line_overlay = new sf::RectangleShape();
            line_overlay->setFillColor(sf::Color(0,0,0,0));
            line_overlay->setOutlineThickness(1);*/
        }
        void onClick(Point& prev, Point& p, bool &newstroke);
        void drawOverlay(bool) const;
        void insert();
};
#endif
