#include "game.h"
#include "shape.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>
void Shape_Rect::onClick(Point& prev, Point& p, bool &newstroke){
    if (newstroke) {
        game->clear_stack();
        prev = p;
        newstroke = false;
    }
    rect_overlay->setSize(sf::Vector2f(p.x - prev.x, p.y - prev.y));
    rect_overlay->setPosition(prev.x,prev.y);
    rect_overlay->setOutlineColor(Game::colors[game->color]);
}
void Shape_Rect::drawOverlay(bool newstroke) const{
    if(!newstroke)game->window.draw(*rect_overlay);
}
void Shape_Rect::insert(){
    Stroke *stroke = new Stroke;
    game->arr.push_back(stroke);
    float x1 = rect_overlay->getPosition().x;
    float y1 = rect_overlay->getPosition().y;
    float width = rect_overlay->getSize().x;
    float height = rect_overlay->getSize().y;
    game->fill_line(stroke, x1,y1,x1+width,y1);
    game->fill_line(stroke, x1+width,y1,x1+width,y1+height);
    game->fill_line(stroke, x1+width,y1+height,x1,y1+height);
    game->fill_line(stroke, x1,y1+height,x1,y1);
}
void Shape_Dot::onClick(Point& prev, Point& p, bool &newstroke){
    static Stroke *stroke = new Stroke;
    if (newstroke) { // this could be improved
        game->clear_stack();
        prev = p;
        newstroke = false;
        stroke = new Stroke();
        game->arr.push_back(stroke);
    }
    game->fill_line(stroke, p.x, p.y, prev.x, prev.y);
    prev = p;
}
void Shape_Dot::drawOverlay(bool)const{}
void Shape_Dot::insert(){}
void Shape_Circle::onClick(Point& prev, Point& p, bool &newstroke){
    if (newstroke) {
        game->clear_stack();
        prev = p;
        newstroke = false;
    }
    float radius = sqrt((prev.x - p.x)*(prev.x - p.x) + (prev.y - p.y)*(prev.y - p.y));
    circle_overlay->setRadius(radius);//sf::Vector2f(p.x - prev.x, p.y - prev.y));
    circle_overlay->setPosition(prev.x - radius,prev.y - radius);
    circle_overlay->setOutlineColor(Game::colors[game->color]);
}
void Shape_Circle::drawOverlay(bool newstroke) const{
    if(!newstroke)game->window.draw(*circle_overlay);
}void Shape_Circle::insert(){
    Stroke *stroke = new Stroke;
    game->arr.push_back(stroke);
    float x1 = circle_overlay->getPosition().x;
    float y1 = circle_overlay->getPosition().y;
    float radius = circle_overlay->getRadius();
    drawCircle(stroke, x1+radius, y1+radius, radius);
}
void Shape_Circle::drawCircle(Stroke* stroke, int x, int y, int rad){
    float dp;       //initialising the descision parameter.
    int x1,y1;
    x1 = 0;            //initialisng the X,Y cordinates.
    y1 = rad;
    dp = 3 - 2*rad;
    while(x1<=y1)
    {
        if(dp<=0)
            dp += (4 * x1) + 6;
        else
        {
            dp += 4*(x1-y1)+10;
            y1--;
        }
        x1++;
        drawEightPoints(stroke, x,y,x1,y1);
    }  
}
void Shape_Circle::drawEightPoints(Stroke* stroke, int xc, int yc, int x, int y){
    stroke->addPoint(Point(x+xc, y+yc, game->color));
    stroke->addPoint(Point(x+xc, -y+yc, game->color));
    stroke->addPoint(Point(-x+xc, -y+yc, game->color));
    stroke->addPoint(Point(-x+xc, y+yc, game->color));

    stroke->addPoint(Point(y+xc, x+yc, game->color));
    stroke->addPoint(Point(y+xc, -x+yc, game->color));
    stroke->addPoint(Point(-y+xc, -x+yc, game->color));
    stroke->addPoint(Point(-y+xc, x+yc, game->color));
}
void Shape_Line::onClick(Point& prev, Point& p, bool &newstroke){
    if (newstroke) {
        game->clear_stack();
        prev = p;
        newstroke = false;
    }
    line_overlay[0].position = sf::Vector2f(prev.x, prev.y);
    line_overlay[0].color  = Game::colors[game->color];
    line_overlay[1].position = sf::Vector2f(p.x, p.y);
    line_overlay[1].color = Game::colors[game->color];
}
void Shape_Line::drawOverlay(bool newstroke) const{
    if(!newstroke)game->window.draw(line_overlay, 2, sf::Lines);
}
void Shape_Line::insert(){
    Stroke *stroke = new Stroke;
    game->arr.push_back(stroke);
    game->fill_line(stroke, line_overlay[0].position.x, line_overlay[0].position.y,
            line_overlay[1].position.x, line_overlay[1].position.y);
}
