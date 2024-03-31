#include "game.h"
#include "shape.h"
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
