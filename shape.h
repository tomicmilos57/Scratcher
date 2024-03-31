#ifndef shape_h
#define shape_h
//#include "point.h"
#include <SFML/Graphics/RectangleShape.hpp>
class Point;
class Game;
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
#endif
